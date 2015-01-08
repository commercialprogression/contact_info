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
    '#type' => 'textarea',
    '#title' => t('Address'),
    '#default_value' => isset($contact_info['contact_address']) ? $contact_info['contact_address'] : '',
  );

  $form['contact_info']['contact_phone'] = array(
    '#type' => 'fieldset',
    '#title' => t('Phone'),
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

  $form['contact_info']['contact_fax'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fax'),
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

  // Fetch social media sites.
  $social_media = contact_info_fetch_social_media();
  
  // Find social media weights.
  if ($social_media) {
    foreach ($social_media as $social_media_key => $social_media_value) {
      $social_media[$social_media_key]['weight'] = $contact_info['social_media'][$social_media_key]['weight'];
    }
    
    // Sort the sites by their weight.
    uasort($social_media, 'contact_info_sort_weight');
  }
  
  $form['contact_info']['social_media'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social media'),
    '#theme' => 'contact_info_social_media_draggable_table',
  );
  
  // Loop through available social media and build out table.
  foreach ($social_media as $key => $value) {
    
    $form['contact_info']['social_media'][$key]['key'] = array(
      '#type' => 'value',
      '#value' => $value['key'],
    );
    
    $form['contact_info']['social_media'][$key]['icon'] = array(
      '#prefix' => '<span class="contact-info-social-icon">',
      '#suffix' => '</span>',
      '#markup' => $value['key'],
    );
    
    $form['contact_info']['social_media'][$key]['name'] = array(
      '#markup' => $value['name'],
    );
    
    $form['contact_info']['social_media'][$key]['url'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($contact_info['social_media'][$key]['url']) ? $contact_info['social_media'][$key]['url'] : '',
    );
    
    $form['contact_info']['social_media'][$key]['enable'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($contact_info['social_media'][$key]['enable']) ? $contact_info['social_media'][$key]['enable'] : '',
    );
    
    $form['contact_info']['social_media'][$key]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => isset($contact_info['social_media'][$key]['weight']) ? $contact_info['social_media'][$key]['weight'] : '',
      '#delta' => 10,
      '#title_display' => 'invisible',
    );

  }
  
  return system_settings_form($form);
}

/**
 * Theme function to render draggable table.
 */
function theme_contact_info_social_media_draggable_table($variables) {
  $form = $variables['form'];
  
  // Add contact info css
  drupal_add_css(drupal_get_path('module', 'contact_info') . '/theme/css/contact_info.css');
  
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