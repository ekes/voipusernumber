<?php

/**
 * @file
 *   Voip user module user settings pages and forms.
 */

/**
 * Menu callback: User number settings page.
 */
function voipuser_settings_page($account) {
  $content = array();

  $content['add'] = l(t('Add number'), '/user/' . $account->uid . '/edit/voipnumber/add');

  $content['numbers'] = drupal_get_form('voipuser_settings_numbers', $account);

  return theme('voipuser_settings_page', $content);
}

/**
 * Form callback: User add number page.
 */
function voipuser_settings_add_form(&$form_state, $account) {
}

/**
 * Form callback: User delet number page.
 */
function voipuser_settings_delete_form(&$form_state, $account, $number) {
}

/**
 * Form: Display numbers, set default, active.
 */
function voipuser_settings_numbers_form(&$form_state, $account) {
  $form = array();
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  foreach ($numbers as $number => $voipnumber) {
    if ($number == 'default') {
      continue;
    }

    $row = array();
    $row['number'] = array(
      '#type' => 'item',
      '#title' => t('Phone number'),
      '#value' => $voipnumber->number,
    );
  }
}

/**
 * Theme user settings page.
 *
 * @param array $content
 *   'add' link and 'numbers' form.
 *
 * @ingroup themeable
 */
function theme_voipuser_settings_page($content) {
  $output = '<div class="voipuser-add">' . $content['add'] . '</div>';
  $output .= $content['numbers'];
  return $output;
}
