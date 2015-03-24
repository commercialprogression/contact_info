<?php

/**
 * @file
 * Tokens for the contact info module.
 */

/**
 * Implements hook_token_info().
 */
function contact_info_token_info() {
  $info = array();
  // Define new token type.
  $info['types']['contact_info'] = array(
    'name' => t('Contact info'),
    'description' => t('Data from the contact info module.'),
  );
  $info['types']['address'] = array(
    'name' => t('Address'),
    'description' => t('Address from the contact info module.'),
    'needs-data' => 'address',
  );
  $info['types']['phone'] = array(
    'name' => t('Phone'),
    'description' => t('Phone from the contact info module.'),
    'needs-data' => 'phone',
  );
  $info['types']['fax'] = array(
    'name' => t('Fax'),
    'description' => t('Fax from the contact info module.'),
    'needs-data' => 'fax',
  );
  $info['types']['social_seo'] = array(
    'name' => t('Social SEO'),
    'description' => t('Social SEO from the contact info module.'),
    'needs-data' => 'social_seo',
  );

  // Define new tokens.
  $info['tokens']['contact_info']['address'] = array(
    'name' => t('Address'),
    'description' => t('The address entered in the contact info form.'),
    'type' => 'address',
  );
  $info['tokens']['address']['country_name'] = array(
    'name' => t('Country name'),
    'description' => t('The country name of the address.'),
  );
  $info['tokens']['address']['legal_name'] = array(
    'name' => t('Legal name'),
    'description' => t('The legal name of the address.'),
  );
  $info['tokens']['address']['street_address'] = array(
    'name' => t('Street address'),
    'description' => t('The street address of the address.'),
  );
  $info['tokens']['address']['locality'] = array(
    'name' => t('Locality'),
    'description' => t('The locality of the address.'),
  );
  $info['tokens']['address']['region'] = array(
    'name' => t('Region'),
    'description' => t('The region of the address.'),
  );
  $info['tokens']['address']['postal_code'] = array(
    'name' => t('Postal code'),
    'description' => t('The postal code of the address.'),
  );
  
  $info['tokens']['contact_info']['phone'] = array(
    'name' => t('Phone number'),
    'description' => t('The phone number entered in the contact info form.'),
    'type' => 'phone',
  );
  $info['tokens']['phone']['label'] = array(
    'name' => t('Label'),
    'description' => t('The label of the phone number.'),
  );
  $info['tokens']['phone']['country_code'] = array(
    'name' => t('Country code'),
    'description' => t('The country code of the phone number.'),
  );
  $info['tokens']['phone']['number'] = array(
    'name' => t('Number'),
    'description' => t('The number of the phone number.'),
  );
  
  $info['tokens']['contact_info']['fax'] = array(
    'name' => t('Fax number'),
    'description' => t('The fax number entered in the contact info form.'),
    'type' => 'fax',
  );
  $info['tokens']['fax']['label'] = array(
    'name' => t('Label'),
    'description' => t('The label of the fax number.'),
  );
  $info['tokens']['fax']['number'] = array(
    'name' => t('Number'),
    'description' => t('The number of the fax number.'),
  );
  
  $info['tokens']['contact_info']['social_seo'] = array(
    'name' => t('Social SEO'),
    'description' => t('The social info useful for metatag and elsewhere.'),
    'type' => 'social_seo',
  );
  $info['tokens']['social_seo']['site_twitter'] = array(
    'name' => t('Site Twitter'),
    'description' => t('The site twitter handle.'),
  );
  $info['tokens']['social_seo']['site_google_plus'] = array(
    'name' => t('Site Google+'),
    'description' => t('The site Google+ URL.'),
  );
  
  $info['tokens']['contact_info']['social'] = array(
    'name' => t('Social links'),
    'description' => t('The social links entered in the contact info form.'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function contact_info_tokens($type, $tokens, array $data = array(), array $options = array()) {
  // Grab contact info data
  $contact_info = variable_get('contact_info', '');

  $replacements = array();

  if ($type == 'contact_info') {
    // Loop through available tokens.
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'address':
          $replacements[$original] = contact_info_address_block();
          break;
        case 'phone':
          $replacements[$original] = contact_info_phone_block();
          break;
        case 'fax':
          $replacements[$original] = contact_info_fax_block();
          break;
        case 'social_seo':
          $replacements[$original] = print_r($contact_info['social_seo'], TRUE);
          break;
        case 'social':
          $replacements[$original] = render(contact_info_social_block());
          break;
      }
    }
    $addresses = token_find_with_prefix($tokens, 'address');
    foreach ($addresses as $name => $original) {
      $replacements[$original] = $contact_info['address'][$name];
    }
    $phones = token_find_with_prefix($tokens, 'phone');
    foreach ($phones as $name => $original) {
      $replacements[$original] = $contact_info['phone'][$name];
    }
    $faxes = token_find_with_prefix($tokens, 'fax');
    foreach ($faxes as $name => $original) {
      $replacements[$original] = $contact_info['fax'][$name];
    }
    $social_seos = token_find_with_prefix($tokens, 'social_seo');
    foreach ($social_seos as $name => $original) {
      $replacements[$original] = $contact_info['social_seo'][$name];
    }
  }

  return $replacements;
}
