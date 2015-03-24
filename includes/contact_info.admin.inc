<?php

/**
 * Callback function for social media block setup.
 */
function contact_info_setup($form, &$form_state) {

  // Load existing contact info
  $contact_info = variable_get('contact_info', '');

  // Make that form a tree.
  $form['#tree'] = TRUE;

  $form['contact_info']['address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#collapsible' => TRUE,
  );
  // Get core countries to avoid a Countries module dependency.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  $form['contact_info']['address']['country_name'] = array(
    '#type' => 'select',
    '#default_value' => isset($contact_info['address']['country_name']) ? $contact_info['address']['country_name'] : 'US',
    '#title' => t('Country'),
    '#options' => country_get_list(),
  );
  $form['contact_info']['address']['legal_name'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['address']['legal_name']) ? $contact_info['address']['legal_name'] : '',
    '#title' => t('Legal Name'),
  );
  $form['contact_info']['address']['street_address'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['address']['street_address']) ? $contact_info['address']['street_address'] : '',
    '#title' => t('Street address'),
  );
  $form['contact_info']['address']['locality'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['address']['locality']) ? $contact_info['address']['locality'] : '',
    '#title' => t('Locality'),
    '#description' => t('The city, township, or administrative area'),
  );
  $form['contact_info']['address']['region'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['address']['region']) ? $contact_info['address']['region'] : '',
    '#title' => t('Region'),
    '#description' => t('For instance, MI if you\'re located in Michigan'),
  );
  $form['contact_info']['address']['postal_code'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($contact_info['address']['postal_code']) ? $contact_info['address']['postal_code'] : '',
    '#title' => t('Postal code'),
  );

  // Phone.
  $form['contact_info']['phone'] = array(
    '#type' => 'fieldset',
    '#title' => t('Phone'),
    '#collapsible' => TRUE,
  );
  $form['contact_info']['phone']['country_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Country code'),
    '#default_value' => isset($contact_info['phone']['country_code']) ? $contact_info['phone']['country_code'] : '',
    '#size' => 4,
  );
  $form['contact_info']['phone']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#default_value' => isset($contact_info['phone']['number']) ? $contact_info['phone']['number'] : '',
  );

  // Fax.
  $form['contact_info']['fax'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fax'),
    '#collapsible' => TRUE,
  );
  $form['contact_info']['fax']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number'),
    '#default_value' => isset($contact_info['fax']['number']) ? $contact_info['fax']['number'] : '',
  );

  // Social SEO.
  $form['contact_info']['social_seo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social SEO'),
    '#description' => t('Social links and accounts that aid search engines.'),
    '#collapsible' => TRUE,
  );
  $form['contact_info']['social_seo']['site_twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Site Twitter'),
    '#description' => t('The Twitter handle for the whole site, like @ao5357'),
    '#default_value' => isset($contact_info['social_seo']['site_twitter']) ? $contact_info['social_seo']['site_twitter'] : '',
  );
  $form['contact_info']['social_seo']['site_google_plus'] = array(
    '#type' => 'textfield',
    '#title' => t('Google+ Page'),
    '#description' => t('URL to site\'s Google+ page, like https://plus.google.com/103212176392756352243/'),
    '#default_value' => isset($contact_info['social_seo']['site_google_plus']) ? $contact_info['social_seo']['site_google_plus'] : '',
  );


  // Social media.
  $form['contact_info']['social'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social media'),
    '#prefix' => '<div id="contact-info-social-media-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
  );

  $form['contact_info']['social']['table'] = array(
    '#theme' => 'contact_info_social_draggable_table',
  );

  // Check to see how many social media rows we need.
  if (isset($contact_info['social']['table']) && !$form_state['rebuild']) {
    $form_state['social_rows'] = count($contact_info['social']['table']);
  }
  elseif (!isset($form_state['social_rows'])) {
    $form_state['social_rows'] = 1;
  }

  for ($i = 1; $i <= $form_state['social_rows']; $i++) {
    $form['contact_info']['social']['table'][$i]['name'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($contact_info['social']['table'][$i]['name']) ? $contact_info['social']['table'][$i]['name'] : '',
    );

    $form['contact_info']['social']['table'][$i]['icon'] = array(
      '#prefix' => '<span class="social">',
      '#suffix' => '</span>',
    );

    // Add icon if any social media rows are present,
    if (isset($contact_info['social']['table'][$i]['url'])) {
      $form['contact_info']['social']['table'][$i]['icon']['link'] = array(
        '#markup' => l($contact_info['social']['table'][$i]['name'], $contact_info['social']['table'][$i]['url']),
      );
    }

    $form['contact_info']['social']['table'][$i]['url'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($contact_info['social']['table'][$i]['url']) ? $contact_info['social']['table'][$i]['url'] : '',
    );

    $form['contact_info']['social']['table'][$i]['enable'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($contact_info['social']['table'][$i]['enable']) ? $contact_info['social']['table'][$i]['enable'] : '',
    );

    $form['contact_info']['social']['table'][$i]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => isset($contact_info['social']['table'][$i]['weight']) ? $contact_info['social']['table'][$i]['weight'] : 10,
    );
  }

  $form['contact_info']['social']['add_social_row'] = array(
    '#type' => 'submit',
    '#value' => t('Add social media'),
    '#submit' => array('contact_info_add_social'),
    '#ajax' => array(
      'callback' => 'contact_info_social_callback',
      'wrapper' => 'contact-info-social-media-wrapper',
    ),
    '#limit_validation_errors' => array(),
  );

  // Show the remove button if more than one row is present.
  if ($form_state['social_rows'] > 1) {
    $form['contact_info']['social']['remove_social_row'] = array(
      '#type' => 'submit',
      '#value' => t('Remove social media'),
      '#submit' => array('contact_info_remove_social'),
      '#ajax' => array(
        'callback' => 'contact_info_social_callback',
        'wrapper' => 'contact-info-social-media-wrapper',
      ),
      '#limit_validation_errors' => array(),
    );
  }

  return system_settings_form($form);
}

/**
 * AJAX callback function for social media rows.
 */
function contact_info_social_callback($form, &$form_state) {
  return $form['contact_info']['social'];
}

/**
 * Submit function for adding additional social media rows.
 */
function contact_info_add_social($form, &$form_state) {
  $form_state['social_rows'] ++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit function for removing additional social media rows.
 */
function contact_info_remove_social($form, &$form_state) {
  $form_state['social_rows'] --;
  $form_state['rebuild'] = TRUE;
}

/**
 * Theme function to render draggable table.
 */
function theme_contact_info_social_draggable_table($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Grab the kids.
  $kids = element_children($form);

  // Loop through the kids.
  foreach ($kids as $kid) {
    $kiddos[$kid] = $form[$kid];
    $kiddos[$kid]['weight'] = $form[$kid]['weight']['#default_value'];
  }

  // Sort the kids by weight. Make the heavy ones feel less important.
  uasort($kiddos, 'contact_info_sort_weight');

  // Build out our draggable table.
  foreach ($kiddos as $key => $value) {

    // Add a weight class. Featherweight...
    $form[$key]['weight']['#attributes']['class'] = array('item-row-weight');

    // Build out the table rows.
    $rows[] = array(
      'data' => array(
        drupal_render($form[$key]['name']),
        drupal_render($form[$key]['icon']),
        drupal_render($form[$key]['url']),
        drupal_render($form[$key]['enable']),
        drupal_render($form[$key]['weight']),
      ),
      // Assign each row a draggable class.
      'class' => array('draggable'),
    );
  }

  // Build out that header.
  $header = array(t('Name'), t('Icon'), t('URL'), t('Enable'), t('Weight'));

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
