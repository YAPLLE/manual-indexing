<?php
/**
 * Magento
 *
 * NOTICE OF LICENSE
 *
 * This source file is subject to the Open Software License (OSL 3.0)
 * that is bundled with this package in the file LICENSE.txt.
 * It is also available through the world-wide-web at this URL:
 * http://opensource.org/licenses/osl-3.0.php
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@magentocommerce.com so we can send you a copy immediately.
 *
 * DISCLAIMER
 *
 * Do not edit or add to this file if you wish to upgrade Magento to newer
 * versions in the future. If you wish to customize Magento for your
 * needs please refer to http://www.magentocommerce.com for more information.
 *
 * @category    Mage
 * @package     Mage_Adminhtml
 * @copyright   Copyright (c) 2009 Irubin Consulting Inc. DBA Varien (http://www.varien.com)
 * @license     http://opensource.org/licenses/osl-3.0.php  Open Software License (OSL 3.0)
 */

/**
 * Adminhtml newsletter queue grid block action item renderer
 *
 * @category   Mage
 * @package    Mage_Adminhtml
 * @author      Magento Core Team <core@magentocommerce.com>
 */

class Digiswiss_Lexusnewsletter_Block_Adminhtml_Newsletter_Queue_Grid_Renderer_Action extends Mage_Adminhtml_Block_Widget_Grid_Column_Renderer_Action
{
    public function render(Varien_Object $row)
    {
        $actions = array();


        if($row->getQueueStatus()==Mage_Newsletter_Model_Queue::STATUS_NEVER) {
//                if(!$row->getSubscribersTotal()==0) {
               if(!$row->getQueueStartAt() && $row->getSubscribersTotal()) {
                $actions[] = array(
                    'url' => $this->getUrl('*/*/start', array('id'=>$row->getId())),
//                     'url' => $this->getUrl('*/*/sending', array('id'=>$row->getId())),
                    'caption'	=> Mage::helper('newsletter')->__('Start')
                );
            }
        } else if ($row->getQueueStatus()==Mage_Newsletter_Model_Queue::STATUS_SENDING) {
            $actions[] = array(
                    'url' => $this->getUrl('*/*/pause', array('id'=>$row->getId())),
                    'caption'	=>	Mage::helper('newsletter')->__('Pause')
            );

            $actions[] = array(
                'url'		=>	$this->getUrl('*/*/cancel', array('id'=>$row->getId())),
                'confirm'	=>	Mage::helper('newsletter')->__('Do you really want to cancel the queue?'),
                'caption'	=>	Mage::helper('newsletter')->__('Cancel')
            );


        } else if ($row->getQueueStatus()==Mage_Newsletter_Model_Queue::STATUS_PAUSE) {

            $actions[] = array(
                'url' => $this->getUrl('*/*/resume', array('id'=>$row->getId())),
                'caption'	=>	Mage::helper('newsletter')->__('Resume')
            );

        }

        $actions[] = array(
            'url'		=>	$this->getUrl('*/newsletter_template/preview',array('id'=>$row->getTemplateId())),
            'caption'   =>  Mage::helper('newsletter')->__('Preview'),
            'popup'	    =>	true
        );

        $this->getColumn()->setActions($actions);
        return parent::render($row);
    }

}
