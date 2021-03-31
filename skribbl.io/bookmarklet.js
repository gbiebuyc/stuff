javascript:(function(){
	
let query = document.getElementById('currentWord').innerHTML;
let url = 'https://www.google.com/images?q=' + query;
window.open(url);

})();
