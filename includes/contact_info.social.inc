<?php

/**
 * Implements hook_social_media_info().
 */
function contact_info_contact_info_social_media_info() {

  $social_media = array(
    'facebook' => array(
      'name' => t('Facebook'),
      'key' => 'f',
    ),
    'google-plus' => array(
      'name' => t('Google Plus'),
      'key' => 'g',
    ),
    'twitter' => array(
      'name' => t('Twitter'),
      'key' => 't',
    ),
  );

  return $social_media;
}
