<?php
/**
 * @file
 *   Views query plugin for uconnect Repo Queries.
 */

/**
 * Views query plugin for the uconnect Repo Api.
 */
class views_uconnect_repo_api_plugin_query extends views_plugin_query {

	function query($get_count = FALSE) {
	}

	function execute(&$view) {
		$a_search_criteria = array();
		// Setup pager
		$view -> init_pager();

		if ($this -> pager) {
			if ($this -> pager -> use_pager()) {
				$this -> pager -> set_current_page($view -> current_page);
			}
		}

		// need to also draw in query term
		//	$collection_id = $this -> options['collections']['collection_id'];
		$repo_base_url = $this -> options['repo_base_url'];
		//$xml_format = (string)trim($this -> options['xml_format']);
		$xml_format = 'nsdl_dc';
		$view_context = '/relation.memberOfCollection//key//collectionRecord/additionalMetadata/ncsCollectionRecord/metadata/record/collection/viewContexts/viewContext:%28UCARConnect%29';
		$num_to_show = $this -> pager -> options['items_per_page'];
		$num_to_skip = ($this -> pager -> current_page) * $this -> pager -> options['items_per_page'];

		// retrieve search filters
		$search_term = '';
		if (isset($view -> query -> request_arguments['term'])) {
			$search_term = (string)$view -> query -> request_arguments['term'];
			$search_term = rawurlencode(preg_replace("/[^A-Za-z0-9 ]/", '', $search_term));
		}
		$a_search_criteria['term'] = rawurlencode($search_term);
		// TODO: account for non-exposed filters
		// UPDATE: cannot find them in any drupal variables.  Am thinking must define default and cannot alter
		// unless the operator is exposed to users.

		//dpm( debug_backtrace() );
		// retrieve ed levels
		$selection_edLevel_op = NULL;
		if (isset($view -> query -> pager -> view -> exposed_data['edLevel_op'])) {
			$selection_edLevel_op = strtoupper($view -> query -> pager -> view -> exposed_data['edLevel_op']);
		}
		if ($selection_edLevel_op == NULL) {
			$selection_edLevel_op = 'AND';
		}
		$a_selection_edLevel = array();
		if (isset($view -> query -> request_arguments['edLevel_filter'])) {
			$a_selection_edLevel = $view -> query -> request_arguments['edLevel_filter'];
			// account for when only single selection allowed
			if (is_string($a_selection_edLevel)) {
				$a_selection_edLevel = array($a_selection_edLevel);
			}

			$this -> remove_key_from_array($a_selection_edLevel, 'Any');
			$this -> remove_key_from_array($a_selection_edLevel, 'All');
		}
		$a_search_criteria['edLevel_filter'] = $a_selection_edLevel;

		if (count($a_selection_edLevel) != 0) {
			foreach ($a_selection_edLevel as $index => $value) {
				$a_selection_edLevel[$index] = '"' . $value . '"';
			}
			$selection_edLevel = urlencode('/key//nsdl_dc/educationLevel:(' . implode(' ' . $selection_edLevel_op . ' ', $a_selection_edLevel) . ')');
		}
		else {
			$selection_edLevel = '';
		}

		// retrieve subjects
		$selection_subject_op = NULL;
		if (isset($view -> query -> pager -> view -> exposed_data['subject_op'])) {
			$selection_subject_op = strtoupper($view -> query -> pager -> view -> exposed_data['subject_op']);
		}
		if ($selection_subject_op == NULL) {
			$selection_subject_op = 'AND';
		}
		$a_selection_subject = array();
		if (isset($view -> query -> request_arguments['subject_filter'])) {
			$a_selection_subject = $view -> query -> request_arguments['subject_filter'];
			// account for when only single selection allowed
			if (is_string($a_selection_subject)) {
				$a_selection_subject = array($a_selection_subject);
			}

			$this -> remove_key_from_array($a_selection_subject, 'Any');
			$this -> remove_key_from_array($a_selection_subject, 'All');
		}

		$a_search_criteria['subject_filter'] = $a_selection_subject;
		if (count($a_selection_subject) != 0) {
			foreach ($a_selection_subject as $index => $value) {
				$a_selection_subject[$index] = '"' . $value . '"';
			}
			$selection_subject = urlencode('/key//nsdl_dc/subject:(' . implode(' ' . $selection_subject_op . ' ', $a_selection_subject) . ')');
		}
		else {
			$selection_subject = '';
		}

		// retrieve resource types
		$selection_type_op = NULL;
		if (isset($view -> query -> pager -> view -> exposed_data['type_op'])) {
			$selection_type_op = strtoupper($view -> query -> pager -> view -> exposed_data['type_op']);
		}
		if ($selection_type_op == NULL) {
			$selection_type_op = 'AND';
		}
		$a_selection_type = array();
		if (isset($view -> query -> request_arguments['type_filter'])) {
			$a_selection_type = $view -> query -> request_arguments['type_filter'];
			// account for when only single selection allowed
			if (is_string($a_selection_type)) {
				$a_selection_type = array($a_selection_type);
			}

			$this -> remove_key_from_array($a_selection_type, 'Any');
			$this -> remove_key_from_array($a_selection_type, 'All');
		}

		$a_search_criteria['type_filter'] = $a_selection_type;
		if (count($a_selection_type) != 0) {
			foreach ($a_selection_type as $index => $value) {
				$a_selection_type[$index] = '"' . $value . '"';
			}
			$selection_type = urlencode('/key//nsdl_dc/type:(' . implode(' ' . $selection_type_op . ' ', $a_selection_type) . ')');
		}
		else {
			$selection_type = '';
		}

		// retrieve collections
		$selection_collection_op = NULL;
		if (isset($view -> query -> pager -> view -> exposed_data['collection_op'])) {
			$selection_collection_op = strtoupper($view -> query -> pager -> view -> exposed_data['collection_op']);

		}
		if ($selection_collection_op == NULL) {
			$selection_collection_op = 'OR';
		}

		$a_selection_collection = array();

		if (isset($view -> query -> request_arguments['collection_filter'])) {
			$a_selection_collection = $view -> query -> request_arguments['collection_filter'];

			// account for when only single selection allowed
			if (is_string($a_selection_collection)) {
				$a_selection_collection = array($a_selection_collection);
			}
			// check if UCAR only selected

			if (in_array('UCAR', $a_selection_collection)) {

				// remove and ensure corresponding collections are selected
				// also remove from request_arguments and add new collections
				$this -> remove_key_from_array($a_selection_collection, 'UCAR');
				$this -> remove_key_from_array($view -> query -> request_arguments['collection_filter'], 'UCAR');
				$this -> remove_key_from_array($view -> exposed_data['collection_filter'], 'UCAR');
				$this -> remove_key_from_array($view -> exposed_input['collection_filter'], 'UCAR');
				$a_ucar_collections = variable_get('uconnect_collections_ucar_only');
				foreach ($a_ucar_collections as $index => $value) {
					if (!in_array($value, $a_selection_collection)) {
						$a_selection_collection[] = $value;
					}
					if (!in_array($value, $view -> query -> request_arguments['collection_filter'])) {
						$view -> query -> request_arguments['collection_filter'][$value] = $value;
						$view -> exposed_data['collection_filter'][$value] = $value;
						$view -> exposed_input['collection_filter'][$value] = $value;
					}
				}
			}
			$this -> remove_key_from_array($a_selection_collection, 'Any');
			$this -> remove_key_from_array($a_selection_collection, 'All');

		}

		$a_search_criteria['collection_filter'] = $a_selection_collection;
		if (count($a_selection_collection) != 0) {
			foreach ($a_selection_collection as $index => $value) {
				$a_selection_collection[$index] = '"' . $value . '"';
			}
			$selection_collection = urlencode('ky:(' . implode(' ' . $selection_collection_op . ' ', $a_selection_collection) . ')');
		}
		else {
			$selection_collection = '';
		}

		// pick additional query params based on source.
		$search_base_url = $this -> get_base_url($repo_base_url);

		// only search if base url is selected
		if ($this -> options['repo_base_url'] != '') {
			/*
			 *
			 * // keep this for now but I may have to hard code in the base url
			 * // most dcs apps are going to have a completely different xml structure anyway
			 if (sizeof($collection_id) > 0) {
			 $ky = '';
			 foreach ($collection_id as $index => $value) {

			 if (gettype($value) == 'string') {
			 if ($ky == '') {
			 $ky = 'ky:%28' . $value . '%29';
			 } else {
			 $ky = $ky . '%20OR%20ky:%28' . $value . '%29';
			 }
			 }
			 }
			 }
			 */

			// init q with search query if available
			if ($search_term != '') {
				$q = '&q=%28%28' . $search_term . '%29%20OR%20stems:%28' . $search_term . '%29%20OR%20title:%28' . $search_term . '%29%20OR%20titlestems:%28' . $search_term . '%29%20OR%20description:%28' . $search_term . '%29%20OR%20descriptionstems:%28' . $search_term . '%29%29%20AND%20' . $view_context . '%20AND%20xmlFormat:' . $xml_format;
			}
			else {
				$q = '&q=xmlFormat:' . $xml_format;
			}

			// include edlevel
			if ($selection_edLevel != '') {
				$q .= '%20AND%20' . $selection_edLevel;
			}

			// include restype
			if ($selection_type != '') {
				$q .= '%20AND%20' . $selection_type;
			}

			// include subject
			if ($selection_subject != '') {
				$q .= '%20AND%20' . $selection_subject;
			}

			// set up url with collections if available
			if ($selection_collection != '') {
				$url = $search_base_url . '&transform=localize&n=' . $num_to_show . '&s=' . $num_to_skip . $q . '%20AND%20%28' . $selection_collection . '%29';

			}
			else {
				$url = $search_base_url . '&transform=localize&n=' . $num_to_show . '&s=' . $num_to_skip . $q;
			}

			// retrieve list of resources
			watchdog('views_uconnect_repo_api', 'DEBUG search service request: %query', array('%query' => $url), WATCHDOG_DEBUG);
    
			$results = drupal_http_request($url);
			
			if ($results->code != '200') {
			    watchdog('views_uconnect_repo_api', 'DEBUG search service request: %request', array('%request' => $results->error), WATCHDOG_DEBUG);
			    return FALSE;
			}
			

			$xml = new SimpleXMLElement($results -> data);

			if ($xml_format == 'nsdl_dc') {
				$this -> views_uconnect_repo_api_process_xml_nsdl_dc($view, $xml, $a_search_criteria);
			}
		}
	}

	/**
	 * Process xml results in nsdl_dc format
	 */
	function views_uconnect_repo_api_process_xml_nsdl_dc(&$view, $xml, $a_search_criteria) {
		// For nsdl_dc
		// total results

		$this -> pager -> total_items = (int)$xml -> Search -> resultInfo -> totalNumResults;
		$this -> pager -> update_page_info();

		foreach ($xml->Search->results->record as $record) {

			$row = new stdClass;
			$row -> items = new stdClass;
			// add search criteria so can be used where needed
			// TODO: there's got to be a better way to do this to make these available
			// without associating the search criteria with every row result
			// TODO:  investigate adding these as a global field or something like that?
			if (!empty($a_search_criteria['term'])) {
				$row -> term = urldecode($a_search_criteria['term']);
			}
			else {
				$row -> term = NULL;
			}
			if (!empty($a_search_criteria['edLevel_filter'])) {
				$row -> items -> edLevel_filter = $a_search_criteria['edLevel_filter'];
			}
			else {
				$row -> items -> edLevel_filter = NULL;
			}
			if (!empty($a_search_criteria['subject_filter'])) {
				$row -> items -> subject_filter = $a_search_criteria['subject_filter'];
			}
			else {
				$row -> items -> subject_filter = NULL;
			}
			if (!empty($a_search_criteria['type_filter'])) {
				$row -> items -> type_filter = $a_search_criteria['type_filter'];
			}
			else {
				$row -> items -> type_filter = NULL;
			}

			// TODO:  for collection filter at this point, the goal is just to make
			// it available to tokens, so may want to resolve this to the collection name
			$row -> items -> collection_filter = $a_search_criteria['collection_filter'];
			// title
			$row -> title = (string)$record -> metadata -> nsdl_dc -> title;
			// description
			$row -> description = (string)$record -> metadata -> nsdl_dc -> description;
			// record id
			$row -> id = (string)$record -> head -> id;

			// url
			$url_link = '';
			foreach ($record -> metadata -> nsdl_dc -> identifier as $index => $url) {
				if ((string)$url -> attributes() -> type == 'dct:URI') {
					$url_link = (string)$url;
				}
			}
			$row -> url = $url_link;

			// edLevel
			$a_edLevel = array();
			foreach ($record -> metadata -> nsdl_dc -> educationLevel as $index => $ed_levels) {
				$a_edLevel[] = (string)$ed_levels;
			}
			// order
			// sort according to grade level order
			//$a_master_order = array('Elementary School', 'Lower Elementary', 'Upper Elementary', 'Middle School', 'High School', 'Higher Education', 'Vocational/Professional Development Education', 'Undergraduate (Lower Division)', 'Undergraduate (Upper Division)', 'Graduate/Professional');
			$a_master_order = variable_get('uconnect_edlevel_master_order');
			$a_temp_list = array();
			foreach ($a_master_order as $index => $data) {
				if (in_array($data, $a_edLevel)) {
					$a_temp_list[] = $data;
				}
			}
			$a_edLevel = $a_temp_list;
			unset($a_temp_list, $a_master_order);
			$row -> items -> edLevel = $a_edLevel;

			// subject
			$a_subject = array();
			foreach ($record -> metadata -> nsdl_dc -> subject as $index => $subj) {
				$a_subject[] = (string)$subj;
			}
			// only include items that are in the display list
			$a_metadata_final = array();
			$a_master = variable_get('uconnect_subject_display_master');
			foreach ($a_subject as $index => $value) {
				$md_exists = array_key_exists($value, $a_master);

				if ($md_exists) {
					$a_metadata_final[] = $value;
				}
			}
			$row -> items -> subject = $a_metadata_final;

			// type
			$a_type = array();
			foreach ($record -> metadata -> nsdl_dc -> type as $index => $typ) {
				if ((string)$typ -> attributes() -> type == 'nsdl_dc:NSDLType') {
					$a_type[] = (string)$typ;
				}

			}
			// only include items that are in the display list
			$a_metadata_final = array();
			$a_master = variable_get('uconnect_restype_display_master');
			foreach ($a_type as $index => $value) {
				$md_exists = array_key_exists($value, $a_master);

				if ($md_exists) {
					$a_metadata_final[] = $value;
				}
			}
			$row -> items -> type = $a_metadata_final;

			// standards
			// standards come from two places
			$a_std = array();
			foreach ($record -> metadata -> nsdl_dc -> conformsTo as $index => $std) {
				if ((string)$std -> attributes() -> type == 'dct:URI') {
					$a_std[] = (string)$std;
				}
			}

			foreach ($record -> relations->relation->record as $index => $std_record) {
				foreach ($std_record->metadata->record->standard as $index2 => $std) {
					if ((string)$std -> alignment -> id -> attributes() -> type == 'ASN') {
						$a_std[] = (string)$std -> alignment -> id;
					}
				}
			}

			$row -> items -> standard = $a_std;

			// collections
			$a_collection = array();

			foreach ($record->allCollectionsMetadata->collectionMetadata as $index => $coll) {
				$a_collection[] = array(
					'name' => (string)$coll -> collectionRecord -> general -> fullTitle,
					'key' => (string)$coll -> collectionRecord -> access -> key
				);
			}
			$row -> items -> collection = $a_collection;

			// new row
			$view -> result[] = $row;
		}

	}

	/**
	 * 	return base search url
	 */
	function get_base_url($repo_base_url) {
		if ($repo_base_url == 'http://uc.dls.ucar.edu/search-api') {
			return $repo_base_url . '?relation=larMetadataProvidedBy&transform=localize&response=allCollectionsMetadata&verb=Search';
		}
		else {
			return $repo_base_url . '?verb=Search';
		}
	}

	/**
	 * ideas for here
	 * collections list for limiting
	 *
	 */
	function option_definition() {
		$options = parent::option_definition();

		$options['repo_base_url'] = array('default' => '', );
		//$options['xml_format'] = array('default' => '', );
		//$options['collections']['collection_id'] = array('default' => '', );

		return $options;
	}

	function options_form(&$form, &$form_state) {
		$form = parent::options_form($form, $form_state);
		$form['repo_base_url'] = array(
			'#type' => 'textfield',
			'#title' => t('Repository base URL'),
			'#description' => t('This is the base URL for the uconnect repository that will be queried.'),
			'#default_value' => $this -> options['repo_base_url'],
		);
		// TODO: refresh list of xmlformats if url changes
		// clear cache, relookup and repopulate
		// TODO: refresh list of collections if url of xmlformats changes
		// clear cache, relookup and repopulate

		//TODO enable lookup and parsing of other xmlFormats
		// only search if base url is selected
		if ($this -> options['repo_base_url'] != '') {
			// xml formats available
			/*$xml = json_decode($this -> retrieveXmlFormats());
			 $options = array();
			 $a_temp = array();
			 foreach ($xml->ListXmlFormats->xmlFormat as $format) {
			 $a_temp[(string)$format] = (string)$format;
			 }

			 foreach ($a_temp as $index => $value) {
			 $options[$index] = t($value);
			 }
			 */
			//$form['xml_format'] = array('#type' => 'select', '#title' => t('XML Format'), '#options' => $options, '#description' => t('This is the xml format for the results retrieved.'), '#default_value' => $this -> options['xml_format'], );

			// collections
			/*
			 *
			 $xml = '';
			 $options = array();
			 $a_temp = array();
			 $xml = json_decode($this -> retrieveCollectionsList());
			 foreach ($xml->ListCollections->collections->collection as $collection) {

			 if ((string)$collection -> additionalMetadata -> dlese_collect -> formatOfRecords == trim($this -> options['xml_format'])) {
			 $a_temp[(string)$collection -> searchKey] = (string)$collection -> renderingGuidelines -> label;
			 }
			 }

			 foreach ($a_temp as $index => $value) {
			 $options[$index] = t($value);
			 }
			 */
			//	$form['collections'] = array('#type' => 'fieldset', '#title' => t('Collections to search over'), '#collapsible' => TRUE, '#collapsed' => FALSE, );
			//	$form['collections']['collection_id'] = array('#type' => 'checkboxes', '#title' => t('Collections'), '#options' => $options, '#description' => t('The ID of the uconnect Collection you want to pull resources from.'), '#default_value' => $this -> options['collections']['collection_id'], );

		}

	}

	/*
	 * retrieve list of xml formats
	 */
	function retrieveXmlFormats() {
		$cache = cache_get('views_uconnect_repo_api_xml_formats_data' . '_' . $this -> options['xml_format'] . '_' . $this -> sanitize($this -> options['repo_base_url']));

		if ($cache) {
			$my_data = $cache -> data;
		}
		else {
			//TODO cache the results of the collections list
			$query = $this -> options['repo_base_url'] . '?verb=ListXmlFormats';
			$results = drupal_http_request($query);
			
			$my_data = json_encode(new SimpleXMLElement($results -> data));
			cache_set('views_uconnect_repo_api_xml_formats_data' . '_' . $this -> options['xml_format'] . '_' . $this -> sanitize($this -> options['repo_base_url']), $my_data, 'cache', time() + 360);
		}

		return $my_data;
	}

	/*
	 * Sanitize function, primarily to remove funky chars from urls
	 */
	function sanitize($filename) {

		$special_chars = array(
			"?",
			"[",
			"]",
			"/",
			"\\",
			"=",
			"<",
			">",
			":",
			";",
			",",
			"'",
			"\"",
			"&",
			"$",
			"#",
			"*",
			"(",
			")",
			"|",
			"~",
			"`",
			"!",
			"{",
			"}"
		);

		$filename = str_replace($special_chars, '', $filename);
		$filename = preg_replace('/[\s-]+/', '-', $filename);
		$filename = trim($filename, '.-_');
		return $filename;
	}

	function remove_key_from_array(&$array, $value) {
		if (($key = array_search($value, $array)) !== false) {
			unset($array[$key]);
		}
	}

}
