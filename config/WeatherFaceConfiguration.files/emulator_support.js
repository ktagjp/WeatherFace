// Something like this to get query variables.
function getQueryParam(variable, default_) {
    var query = location.search.substring(1);
    var vars = query.split('&');
    for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if (pair[0] == variable)
            return decodeURIComponent(pair[1]);
    }
    return default_ || false;
}

var return_to = getQueryParam('return_to', 'pebblejs://close#');
document.location = return_to + encodeURIComponent(JSON.stringify(some_settings));
