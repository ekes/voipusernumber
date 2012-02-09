<?php

/**
 * @file
 *   Default VoIP scripts for interecting with VoIP user.
 */

/**
 * Automatically log in dialled-in user, by telephone number.
 *
 * @param string $number
 *   Phone number. For example from the script %caller_number variable.
 * @param bool $create
 *   (optional) If number is not known create a new user. Default FALSE.
 */
function _voipusernumber_autologin_script($number, $create = FALSE) {
  $script = new VoipScript('voipusernumber_autologin');
  // autoload _should_ negate the need for this
  module_load_include('inc', 'voipusernumber', 'voipusernumber.voipusernumber');

  $uid = VoipUserNumber::getUidFromNumber($number);
  if ($uid) {
    global $user;
    watchdog('voipusernumber', 'Voip call associated with user %name.', array('%name' => $user->name));
    $user = user_load($uid);
  }
  elseif ($create) {
    $uid = voipusernumber_user_create($number);
    global $user;
    $user = user_load($uid);
  }
  return $script;
}

/**
 * Log out user.
 */
function _voipusernumber_logout_script() {
  $script = new VoipScript('voipusernumber_logout');
  global $user;
  watchdog('user', 'Voip call disassociated with user %name.', array('%name' => $user->name));
  $user = user_load(0);
  return $script;
}
