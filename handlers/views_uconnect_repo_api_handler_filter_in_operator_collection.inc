<?php
/*
 * @file
 * Definition of views_handler_filter_in_operator.
 */

/**
 * Simple filter to handle matching of multiple options selectable via checkboxes
 *
 * Definition items:
 * - options callback: The function to call in order to generate the value options. If omitted, the options 'Yes' and 'No' will be used.
 * - options arguments: An array of arguments to pass to the options callback.
 *
 * @ingroup views_filter_handlers
 */
class views_uconnect_repo_api_handler_filter_in_operator_collection extends views_handler_filter_in_operator {

	function query() {
		//$this->field_alias = $this->real_field;
		$this -> query -> request_arguments[$this -> real_field] = $this -> value;
	}

	function get_value_options() {
		if (isset($this -> value_options)) {
			return;
		}
		// TODO: limit by options selected xml_format
		
		// retrieve vocab term
		$a_master = variable_get('uconnect_collection_master');
		$a_options = array();

		$a_options['UCAR'] = 'UCAR Only';
		foreach ($a_master as $index => $value) {
			if($value['xml_format'] == 'nsdl_dc'){
				$a_options[$value['id']] = $value['name'];
			}
			if (count($value['children']) > 0) {
				foreach ($value['children'] as $index2 => $value2) {
					if($value2['xml_format'] == 'nsdl_dc'){
						$a_options[$value2['id']] = '-' . $value2['name'];
					}
					if (count($value2['children']) > 0) {
						foreach ($value2['children'] as $index3 => $value3) {
							if($value3['xml_format'] == 'nsdl_dc'){
								$a_options[$value3['id']] = '-' . $value3['name'];
							}
						}
					}
				}
			}

		}
		$this -> value_options = $a_options;
	}

/**
	 * This kind of construct makes it relatively easy for a child class
	 * to add or remove functionality by overriding this function and
	 * adding/removing items from this array.
	 */
	function operators() {
		$operators = array(
			'or' => array(
				'title' => t('Is one of'),
				'short' => t('or'),
				'short_single' => t('='),
				'method' => 'op_helper',
				'values' => 1,
				'ensure_my_table' => 'helper',
			),
			'and' => array(
				'title' => t('Is all of'),
				'short' => t('and'),
				'short_single' => t('='),
				'method' => 'op_helper',
				'values' => 1,
				'ensure_my_table' => 'helper',
			),
		);

		return $operators;
	}

}
