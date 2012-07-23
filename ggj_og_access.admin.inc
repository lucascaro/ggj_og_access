<?php
/**
 * @file
 * GGJ OG Access administration functions.
 *
 * Defines settings forms and administrative actions.
 */

/**
 * Form constructor for ggj_og_access_settings_form
 */
function ggj_og_access_settings_form(&$form_state) {
  // Get all group post types.
  $node_types = og_get_types('group');
  foreach ($node_types as $type) {
    $types[$type] = $type;
  }
  $form['ggj_og_access_types'] = array(
    '#title' => t('Read Only Group Types'),
    '#description' => t('Select which content types are going to be read-only.'),
    '#type' => 'checkboxes',
    '#options' => $types,
    '#default_value' => ggj_og_access_get_types(),
  );
  $form['#submit'][] = 'ggj_og_access_settings_form_submit';
  
  return system_settings_form($form);
}

/**
 * Form submit handler for ggj_og_access_settings_form.
 */
function ggj_og_access_settings_form_submit() {
  // Refresh all cached access control.
  node_access_needs_rebuild(TRUE);
  menu_rebuild();
}