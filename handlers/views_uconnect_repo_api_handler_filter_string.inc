<?php

/**
 * @file
 * Definition of views_handler_filter_string.
 */

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 *
 * @ingroup views_filter_handlers
 */
class views_uconnect_repo_api_handler_filter_string extends views_handler_filter_string {
  function query() {
	//$this->field_alias = $this->real_field;
	$this->query->request_arguments[$this->real_field] = $this->value;
  }
  
  function operator_options($which = 'title') {
    return array(
      '=' => t('Search result contains'),
    );
  }
}
// https://www.drupal.org/node/1239866