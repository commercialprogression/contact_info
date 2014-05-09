<?php

/**
 * Callback function for social media block setup.
 */
function contact_info_setup($form, &$form_state) {

  // Load existing contact info
  $contact_info = variable_get('contact_info', '');

  $form = array(
    '#tree' => TRUE,
  );

  $form['contact_info']['contact_address'] = array(
    '#type' => 'textarea',
    '#title' => t('Address'),
    '#default_value' => isset($contact_info['contact_address']) ? $contact_info['contact_address'] : '',
  );

  $form['contact_info']['contact_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number'),
    '#default_value' => isset($contact_info['contact_phone']) ? $contact_info['contact_phone'] : '',
  );

  $form['contact_info']['social_media'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social media'),
    '#collapsible' => TRUE,
  );

  // Fetch social media sites.
  $social_media = contact_info_fetch_social_media();

  // Build options array.
  foreach ($social_media as $key => $value) {
    $options[$key] = $value['name'];
  }

  // Grab any selected social media sites.
  $social_media_sites = $contact_info['social_media']['social_media_sites'];

  // Build checkboxes.
  $form['contact_info']['social_media']['social_media_sites'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => isset($contact_info['social_media']['social_media_sites']) ? $contact_info['social_media']['social_media_sites'] : array(),
  );

  // Loop through each site and create a URL field.
  if ($social_media_sites) {

    // Set weight options.
    for ($i = 1; $i <= count($social_media_sites); $i++) {
      $weight_options[] = $i;
    }

    // Build social media form.
    $form['contact_info']['social_media']['social_description'] = array(
      '#markup' => '<p>' . t('Please enter a URL and a weight for each social media site.') . '</p>',
    );
    foreach ($social_media_sites as $social_media_site) {
      if ($social_media_site) {
        $form['contact_info']['social_media'][$social_media_site] = array(
          '#type' => 'fieldset',
          '#title' => t('%social_media_site', array('%social_media_site' => $social_media[$social_media_site]['name'])),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        $form['contact_info']['social_media'][$social_media_site]['url'] = array(
          '#title' => t('URL'),
          '#type' => 'textfield',
          '#default_value' => isset($contact_info['social_media'][$social_media_site]['url']) ? $contact_info['social_media'][$social_media_site]['url'] : '',
          '#required' => TRUE,
        );
        $form['contact_info']['social_media'][$social_media_site]['weight'] = array(
          '#title' => t('Weight'),
          '#type' => 'select',
          '#options' => $weight_options,
          '#default_value' => isset($contact_info['social_media'][$social_media_site]['weight']) ? $contact_info['social_media'][$social_media_site]['weight'] : '',
          '#required' => TRUE,
        );
      }
    }
  }

  return system_settings_form($form);
}
