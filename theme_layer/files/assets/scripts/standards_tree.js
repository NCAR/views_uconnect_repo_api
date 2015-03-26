(function ($) {
	
	Drupal.behaviors.uconnectstandards = {

    attach: function (context, settings) { 
    	$('.view-ucarconnect-search .views-row').each(function(i,obj){
    		// get id
    		var classname = $(this).attr('class');
    		// split by spaces and get second one and rip off text
    		var parts = classname.split(" ");
    		var id = parts[1].replace('views-row-','');
    		
    		// add button/link
    		$('.'+parts[1]+' .views-field-standard span.field-content').before('<div class="std_toggle" id="std_toggle_'+id+'">Show Standards</div>');
    		// add id to content
    		$('.'+parts[1]+' .views-field-standard span.field-content').attr('id','std_content_'+id);
    	});
    	// hide all standards
    	$('.views-field-standard span.field-content').addClass('closed');
    	
    	// add toggle functionality 
    	$('.std_toggle').click(function(){
    		// get id
    		var id = $(this).attr('id').replace('std_toggle_','');
    		var content_id = 'std_content_'+id;
    		// swap text
    		if($('#std_toggle_'+id).text() == 'Show Standards'){
    			$('#std_toggle_'+id).text('Hide Standards');
    			$('#'+content_id).removeClass('closed');
    			$('#'+content_id).addClass('open');
    		} else {
    			$('#std_toggle_'+id).text('Show Standards');
    			$('#'+content_id).addClass('closed');
    			$('#'+content_id).removeClass('open');
    		}
    	});
   }
   
 };
})(jQuery);
