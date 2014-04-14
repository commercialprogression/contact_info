<?php

/**
 * Callback function for social media block setup.
 */
function contact_info_setup($form, &$form_state) {

  $form['contact_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact information'),
  );

  $form['contact_info']['contact_address'] = array(
    '#type' => 'textarea',
    '#title' => t('Address'),
  );

  $form['contact_info']['contact_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number'),
  );

  $form['social_media'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social media'),
  );

  $options = array(
    'facebook' => t('Facebook'),
    'google-plus' => t('Google Plus'),
    'twitter' => t('Twitter'),
  );

  $form['social_media']['social_media_sites'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('social_media_sites', array()),
  );

  // Grab any selected social media sites.
  $social_media_sites = variable_get('social_media_sites', array());
  // Loop through each site and create a URL field.
  if ($social_media_sites) {
    $form['social_media']['social_description'] = array(
      '#markup' => '<p>' . t('Please enter an URL for each selected social media site.') . '</p>',
    );
    foreach ($social_media_sites as $social_media_site) {
      if ($social_media_site) {
        $form['social_media']['social_media_' . $social_media_site] = array(
          '#title' => t('%social_media_site URL', array('%social_media_site' => $social_media_site)),
          '#type' => 'textfield',
          '#default_value' => variable_get('social_media_' . $social_media_site),
        );
      }
    }
  }

  return system_settings_form($form);
}

