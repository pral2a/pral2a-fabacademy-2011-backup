/*
The Gerani Engine a funny ajax display engine based on jQuery for my Fab Academy Site.
Pral2a, 2011. hi@pral2a.com
Source avaible. Optimized with The Closure Compiler by Google.
Creative Commons Attribution-Share Alike 3.0
*/


$(document).ready(function() {
		
$.ajaxSetup ({

// Disable caching of AJAX responses
	cache: false
});

	
// Gerani window Dragg, Follows, Toggle options

$("#window").draggable();

// The window 	

$("#menu").change(function () {
		
//		var base_url = window.location.pathname; //do it auto

		var base_url = "http://academy.cba.mit.edu/labs/barcelona/guillem.camprodon";

		var project;
		var page;
		var display_url;		
		
		// Reset the loading bar		
		unloadbar();
			
				
		// Set the state selector selected at the same index as the page selector
		$('#state option').attr("selected", "");
		var index_id = $('#pages').attr("selectedIndex");
		$('#state option:eq('+index_id+')').attr("selected", "selected");

		
		
		// Read the state of the page selector		
		$("#pages option:selected").each(function () {
			project = $(this).val();
			title = $(this).text();
		});
		
		
		
		// Read the state of the section/content selector
		$("#section option:selected").each(function () {
			section = $(this).val();	
		});		
		
		
		// Build the page link		
		page = "content/" + project + "/" + project + ".html";

		
		// Gets and displays the info
		if (section == "img") {
			$.get(page, function(content) {
			var $html = $(content);
			var $code = $html.filter('img');
			loadbar();
			$('#content').html($code);
			redirectimage();
			});	
		} 
		else if (section == "code") {
			$.get(page, function(content) {
			var $html = $(content);
			var $code = $html.filter('code');
			loadbar();
			$('#content').html($code);
			redirectimage();
			});	
		}
		else if (section == "text") {
			$.get(page, function(content) {
			var $html = $(content);
			var $code = $html.filter('p');
			loadbar();		
			$('#content').html($code);
			redirectimage();
			});	
		}
		else if (section == "links") {
			$.get(page, function(content) {
			var $html = $(content);
			var $code = $html.filter('a');
			loadbar();		
			$('#content').html($code);
			redirectimage();
			});	
		}  
		else {	
						
			// Section link
			
			if (section != "all") {			
				page = page + " #" + section; 
			}
			
			// Displays rel info
			
			$('#content').load(page, function() {
            	loadbar();
            	redirectimage();
            });
		}
		
		$("#content").text("UNABLE TO FIND CONTENT TO DISPLAY");

		function loadbar(){
		  $(".loadbar").animate({
		    width: "200px",
		  }, 1000 );
		}
		function unloadbar(){
		  $(".loadbar").animate({
		    width: "0px",
		  }, 200 );
		}
		
		// Image redirect the source engine
		
		function redirectimage(){
			$('img').each(function(){       
			        var image = $(this).attr("src");
					var imageSrc = "content/" + project + "/" + $(this).attr("src");;
					$(this).attr("src", imageSrc);		
			 });
		}
		
		window.location.hash = project;
		
		display_url = base_url + "/" + page;
		var link = "<a href=" + display_url + ">" + display_url + "</a>";
				
		$("#title").text(title);       
		$("#url").html(link);
		$("#section-title").text(section);
			
		})
		

		
		.trigger('change');
		
});	  
