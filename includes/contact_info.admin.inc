<?php

/**
 * Callback function for social media block setup.
 */
function contact_info_setup($form, &$form_state) {

  // Load existing contact info
  $contact_info = variable_get('contact_info', '');

  // Make that form a tree.
  $form['#tree'] = TRUE;

  $form['contact_info']['contact_address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#collapsible' => TRUE,
  );
  // Get core countries to avoid a Countries module dependency.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  $form['contact_info']['contact_address']['country-name'] = array(
    '#type' => 'select',
    '#default_value' => isset($contact_info['contact_address']['country-name']) ? $contact_info['contact_address']['country-name'] : 'US',
    '#title' => t('Country'),
    '#options' => country_get_list(),
  );
  $form['contact_info']['contact_address']['legalName'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['contact_address']['legalName']) ? $contact_info['contact_address']['legalName'] : '',
    '#title' => t('Legal Name'),
  );
  $form['contact_info']['contact_address']['street-address'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['contact_address']['street-address']) ? $contact_info['contact_address']['street-address'] : '',
    '#title' => t('Street address'),
  );
  $form['contact_info']['contact_address']['locality'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['contact_address']['locality']) ? $contact_info['contact_address']['locality'] : '',
    '#title' => t('Locality'),
    '#description' => t('The city, township, or administrative area'),
  );
  $form['contact_info']['contact_address']['region'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['contact_address']['region']) ? $contact_info['contact_address']['region'] : '',
    '#title' => t('Region'),
    '#description' => t('For instance, MI if you\'re located in Michigan'),
  );
  $form['contact_info']['contact_address']['postal-code'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['contact_address']['postal-code']) ? $contact_info['contact_address']['postal-code'] : '',
    '#title' => t('Postal code'),
  );

  // Phone.
  $form['contact_info']['contact_phone'] = array(
    '#type' => 'fieldset',
    '#title' => t('Phone'),
    '#collapsible' => TRUE,
  );
  $form['contact_info']['contact_phone']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#description' => t('Optionally, provide a label for the phone field.'),
    '#default_value' => isset($contact_info['contact_phone']['label']) ? $contact_info['contact_phone']['label'] : '',
  );
  $form['contact_info']['contact_phone']['country_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Country code'),
    '#default_value' => isset($contact_info['contact_phone']['country_code']) ? $contact_info['contact_phone']['country_code'] : '',
    '#size' => 4,
  );
  $form['contact_info']['contact_phone']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#default_value' => isset($contact_info['contact_phone']['number']) ? $contact_info['contact_phone']['number'] : '',
  );

  // Fax.
  $form['contact_info']['contact_fax'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fax'),
    '#collapsible' => TRUE,
  );
  $form['contact_info']['contact_fax']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#description' => t('Optionally, provide a label for the fax field.'),
    '#default_value' => isset($contact_info['contact_fax']['label']) ? $contact_info['contact_fax']['label'] : '',
  );
  $form['contact_info']['contact_fax']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#default_value' => isset($contact_info['contact_fax']['number']) ? $contact_info['contact_fax']['number'] : '',
  );

  return system_settings_form($form);
}

/**
 * Theme function to render draggable table.
 */
function theme_contact_info_social_media_draggable_table($variables) {
  $form = $variables['form'];
  
  // Initialize the variable which will store our table rows.
  $rows = array();

  // Loop through the kids.
  foreach (element_children($form) as $id) {

    // Add a weight class. Featherweight...
    $form[$id]['weight']['#attributes']['class'] = array('item-row-weight');
    
    // Build out the table rows.
    $rows[] = array(
      'data' => array(
        drupal_render($form[$id]['name']),
        drupal_render($form[$id]['url']),
        drupal_render($form[$id]['icon']),
        drupal_render($form[$id]['enable']),
        drupal_render($form[$id]['weight']),
      ),
      // Assign each row a draggable class.
      'class' => array('draggable'),
    );
  }

  // Build out that header.
  $header = array(t('Name'), t('URL'), t('Icon'), t('Enable'), t('Weight'));

  // Declare table id.
  $table_id = 'items-table';
  
  // Put the table together.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // Add that drag.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'item-row-weight');

  return $output;
}
