<?php

/**
 * Callback function for social media block setup.
 */
function social_media_block_setup($form_state) {
  $form = array();

  $options = array(
    'facebook' => t('Facebook'),
    'google-plus' => t('Google Plus'),
    'twitter' => t('Twitter'),
  );

  $form['social_media_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social media types'),
  );

  $form['social_media_types']['social_media_sites'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('social_media_sites', array()),
  );

  return system_settings_form($form);
}
