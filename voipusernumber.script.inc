<?php

/**
 * @file
 *   Default VoIP scripts for interecting with VoIP user.
 */

/**
 * Automatically log in dialled-in user, by telephone number.
 *
 * If a user is related to the $number, or a user is created
 * they, will be logged into the Drupal global $user. The
 * script %uid and %username will also be set.
 *
 * If there is no user associated with the number, and none is created user
 * 0 (anonymous) will be stored in the variables.
 *
 * In the script that calls this script use of global $user
 * will return the value set at the initialization of the script. Further
 * scripts called and initialized after this script is called will have the
 * global available. The scrip variables %user_uid and %user_name values within
 * the calling script script.
 *
 * Example:
 *   $script->addGosub(
 *     'voipusernumber_autologin',
 *     array(
 *       'number' => '%caller_number',
 *       'create' => TRUE,
 *     )
 *   );
 *
 * @param string $number
 *   Phone number. For example from the script %caller_number variable.
 * @param bool $create
 *   (optional) If number is not known create a new user. Default FALSE.
 */
function _voipusernumber_autologin_script($number, $create = FALSE) {
  global $user;
  $script = new VoipScript('voipusernumber_autologin');
  // Autoload _should_ negate the need for this.
  module_load_include('inc', 'voipusernumber', 'voipusernumber.voipusernumber');

  $uid = VoipUserNumber::getUidFromNumber($number);
  if ($uid) {
    $user = user_load($uid);
    watchdog('voipusernumber', 'Voip call associated with user %name.', array('%name' => $user->name));
  }
  elseif ($create) {
    $uid = voipusernumber_user_create($number);
    $user = user_load($uid);
    watchdog('voipusernumber', 'Voip call account created and associated with user %name.', array('%name' => $user->name));
  }
  else {
    $user = user_load(0);
  }

  $script->addSet('user_uid', $user->uid);
  $script->addSet('user_name', $user->name);

  return $script;
}

/**
 * Log out user.
 *
 * Sets global $user and script %user_uid, %user_name to user 0.
 */
function _voipusernumber_logout_script() {
  $script = new VoipScript('voipusernumber_logout');
  global $user;
  watchdog('user', 'Voip call disassociated with user %name.', array('%name' => $user->name));
  $user = user_load(0);
  $script->addSet('user_uid', $user->uid);
  $script->addSet('user_name', $user->name);
  return $script;
}
