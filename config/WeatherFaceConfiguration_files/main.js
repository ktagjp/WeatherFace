(function(){
var KasperskyLab=function(e){function l(a){return"undefined"===typeof a?"undefined":null===a?"null":Object.prototype.toString.call(a).match(/^\[object\s(.*)\]$/)[1]}function f(a){if(null===a||Infinity==a||-Infinity==a||a===k)return"null";var d=l(a);if("Boolean"==d)return""+a;if("Number"==d)return window.isNaN(a)?"null":""+a;if("String"==d)return'"'+a+'"';if("object"==typeof a){f.check||(f.check=[]);for(var c=0,b=f.check.length;c<b;++c)if(f.check[c]===a)throw new TypeError;f.check.push(a);c="";if("Array"==
d){for(var d=0,e=a.length;d<e;++d)c+=f(a[d])+",";f.check.pop();return"["+c.slice(0,-1)+"]"}for(e in a)a.hasOwnProperty(e)&&(c+='"'+e+'":'+f(a[e])+",");f.check.pop();return"{"+c.slice(0,-1)+"}"}return k}var g,h,k;if("object"==typeof window.JSON&&window.JSON&&window.JSON.stringify&&window.JSON.parse&&(g=window.JSON.parse,h=window.JSON.stringify,"function"==typeof h&&"function"==typeof g))return e.JSONStringify=h,e.JSONParse=g,e;h=function(a){return f(a)};var m={source:null,b:/^[\x20\t\n\r]*(?:([,:\[\]{}]|true|false|null)|(-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)|"((?:[^\r\n\t\\\"]|\\(?:["\\\/trnfb]|u[0-9a-fA-F]{4}))*)")/,
a:function(){throw new SyntaxError("JSON syntax error");},c:function(a){this.source=a.input.slice(a[0].length);return this.b.exec(this.source)},f:function(){for(var a=this.b.exec(this.source),d=a&&"]"!=a[1],c=[];;a=this.c(a)){a||this.a();if(d)c.push(this.d(a)),a=this.b.exec(this.source);else if(a[1])if("]"==a[1])break;else","!=a[1]&&this.a();else this.a();d=!d}return c},g:function(){for(var a,d=!0,c={},b=this.b.exec(this.source);;b=this.c(b))if(b||this.a(),d){if(b[1]&&"}"==b[1])break;else(b[1]||b[2]||
!b[3])&&this.a();a=b[3];(b=this.c(b))&&b[1]&&":"==b[1]||this.a();d=!1}else{a||this.a();c[a]=this.d(b);b=this.c(this.b.exec(this.source));if(b[1])if("}"==b[1])break;else","!=b[1]&&this.a();else this.a();a=k;d=!0}return c},d:function(a){if(a[1])switch(a[1]){case "[":return this.source=this.source.slice(a[0].length),this.f();case "{":return this.source=this.source.slice(a[0].length),this.g();case "true":return!0;case "false":return!1;case "null":return null;default:this.a()}else if(a[2])return+a[2];
return a[3].replace(/\\(?:u(.{4})|(["\\\/\']))/g,function(a,c,b){return c?String.fromCharCode(parseInt(c,16)):b})},e:function(a){if("String"!=l(a))throw new TypeError;this.source=a;(a=this.b.exec(this.source))||this.a();return this.d(a)}};g=function(a){return m.e(a)};e.JSONStringify=h;e.JSONParse=g;return e}.call(this,KasperskyLab||{});
var KasperskyLab=function(a){function h(b){var c="",d=0;b=b.replace(/\r\n/g,"\n");for(var e="",m=b.length,f=0;f<m;++f){var a=b.charCodeAt(f);128>a?e+=String.fromCharCode(a):(127<a&&2048>a?e+=String.fromCharCode(a>>6|192):(e+=String.fromCharCode(a>>12|224),e+=String.fromCharCode(a>>6&63|128)),e+=String.fromCharCode(a&63|128))}b=e;for(e=b.length;d<e;){var h=b.charCodeAt(d++),m=b.charCodeAt(d++),f=b.charCodeAt(d++),a=h>>2,h=(h&3)<<4|m>>4,k=(m&15)<<2|f>>6,g=f&63;isNaN(m)?k=g=64:isNaN(f)&&(g=64);c=c+"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".charAt(a)+
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".charAt(h)+"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".charAt(k)+"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".charAt(g)}return c}function g(b){var c="",d=0;b=b.replace(/[^A-Za-z0-9\+\/\=]/g,"");for(var e=b.length;d<e;){var a="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".indexOf(b.charAt(d++)),f="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".indexOf(b.charAt(d++)),
h="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".indexOf(b.charAt(d++)),g="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=".indexOf(b.charAt(d++)),k=(f&15)<<4|h>>2,p=(h&3)<<6|g,c=c+String.fromCharCode(a<<2|f>>4);64!=h&&(c+=String.fromCharCode(k));64!=g&&(c+=String.fromCharCode(p))}b=c;c="";f=b.length;for(d=0;d<f;)e=b.charCodeAt(d),128>e?(c+=String.fromCharCode(e),d++):191<e&&224>e?(a=b.charCodeAt(d+1),c+=String.fromCharCode((e&31)<<6|a&63),d+=2):(h=b.charCodeAt(d+
2),a=b.charCodeAt(d+1),c+=String.fromCharCode((e&15)<<12|(a&63)<<6|h&63),d+=3);return c}a.DecodeParameters=function(b){var c=[],d=b.responseText;b=b.getResponseHeader("KL-Kas-Content-type");d&&("json"==b?c=KasperskyLab.JSONParse(g(d)):c.push(g(d)));return c};a.EncodeParameters=function(b,c){switch(b.length){case 0:break;case 1:c.setRequestHeader("KL-Kas-Content-type","text");c.setRequestHeader("KL-Kas-Parameters",h(b[0]));break;default:c.setRequestHeader("KL-Kas-Content-type","json"),c.setRequestHeader("KL-Kas-Parameters",
h(KasperskyLab.JSONStringify(b)))}};return a}(KasperskyLab||{}),KasperskyLab=function(a){var h=!window.XMLHttpRequest||!!window.document.namespaces&&window.navigator.userAgent.match(/MSIE 7.0/),g=h?null:window.XMLHttpRequest.prototype.open,b=h?null:window.XMLHttpRequest.prototype.send;a.GetXmlHttp=function(){try{return new ActiveXObject("Microsoft.XMLHTTP")}catch(c){}try{var d=new window.XMLHttpRequest;d.open=g;d.send=b;return d}catch(a){}return null};a.Log=function(b){};return a}(KasperskyLab||{}),
KasperskyLab=function(a){a.MaxRequestDelay=2E3;a.GetResourceSrc=function(a){return"F5800B1D7703080874D4FAFC381CC6A2"+a};a.AddEventListener=function(a,g,b){"addEventListener"in a?a.addEventListener(g,function(c){b(c||window.event)},!1):a.attachEvent("on"+g,function(c){b.call(a,c||window.event)})};a.AddStyles=function(a){if("object"==typeof a&&a.constructor==Array){var g=document.createElement("style");g.type="text/css";for(var b=0,c=a.length;b<c;++b){var d=g,e=a[b];d.styleSheet?d.styleSheet.cssText+=e+"\n":d.appendChild(document.createTextNode(e))}document.head?
document.head.appendChild(g):document.getElementsByTagName("head")[0].appendChild(g)}};a.GetCurrentTime=function(){return(new Date).getTime()};return a}(KasperskyLab||{}),KasperskyLab=function(a){a.Balloon=function(a,g,b,c){function d(){q&&clearTimeout(q);q=0}function e(){d()}function m(b){q||(d(),q=setTimeout(function(){k()},200))}function f(b){c&&c(b||window.event)&&k()}function s(){n||(KasperskyLab.AddStyles([".kisb * { position: relative; display:block; overflow-x:hidden; width: auto; margin:0; padding:0; font-family: Verdana; line-height: 150%; text-indent:0; border:0; text-align:left; box-sizing:content-box; letter-spacing: normal;}",
".kisb { z-index:10000; width: 280px; cursor:default; display:block;}",".kisb a { text-decoration: underline; display:inline-block; }",".kisb a:hover { text-decoration: none; }",".kisb a, .kisb a:link, .kisb a:hover, .kisb a:visited { color: #008ccc;}"]),n=!0);var a=document.createElement("div");a.className="kisb";a.id=t;a.onmouseout=m;a.onmouseover=e;a.onclick=f;b(a);a.style.visibility="hidden";document.body.appendChild(a);return a}function r(a){a=a.getBoundingClientRect();return{width:a.width?a.width:
a.right-a.left,height:a.height?a.height:a.bottom-a.top}}function k(){l&&(l.style.visibility="hidden")}function p(a,b,c){l||(l=s());var e=0,f=0,f=r(l);if(1==g)e=a,f=b-(f.height?f.height:20);else if(2==g)var e=document.documentElement.clientWidth||document.body.clientWidth,h=f.width/2,e=h>a?0:h+a>e?e-f.width:a-h,f=b+f.height>(document.documentElement.clientHeight||document.body.clientHeight)?b-f.height:b;else e=a,f=b;f+=document.documentElement&&document.documentElement.scrollTop||document.body.scrollTop;
e+=document.documentElement&&document.documentElement.scrollLeft||document.body.scrollLeft;l.style.position="absolute";l.style.left=Math.round(e).toString()+"px";l.style.top=Math.round(f).toString()+"px";l.style.visibility="visible";d();q=setTimeout(function(){k()},c)}var n=!1,l=null,q=null,t="balloon_parent_div_"+a;this.ShowBalloon=function(a,b,c){d();b?q=setTimeout(function(){var b=a();b.isNeed?p(b.x,b.y,c):k()},b):(b=a(),p(b.x,b.y,c))}};return a}(KasperskyLab||{}),KasperskyLab=function(a){a.CallSender=
function(a,g){var b="/"+a+"/"+g+"/to/";this.Call=function(a,d,e,g){try{var f=KasperskyLab.GetXmlHttp();f||g&&g(-1);f.open("GET",b+a);KasperskyLab.EncodeParameters(d,f);var h=setTimeout(function(){f.abort();g&&g(-1)},12E4);f.onreadystatechange=function(){if(4==f.readyState){clearTimeout(h);h=null;f.onreadystatechange=function(){};var a=f.status;200==a&&e?(a=KasperskyLab.DecodeParameters(f),e(f.getResponseHeader("KL-Kas-Result"),a),f=null):(f=null,g&&g(a))}};f.send(null)}catch(r){g&&g(-1)}}};return a}(KasperskyLab||
{}),KasperskyLab=function(a){a.CallReceiver=function(a,g){function b(){try{n&&clearTimeout(n)}catch(a){}try{l&&(l.onreadystatechange=function(){},l.abort())}catch(b){}l=n=null}function c(){for(var a in k)if(k.hasOwnProperty(a))return!1;return!0}function d(){var a=KasperskyLab.MaxRequestDelay,b=KasperskyLab.GetCurrentTime(),c;for(c in k)try{var d=k[c].onPing;if(d){var e=d(b);e<a&&1<e&&e<KasperskyLab.MaxRequestDelay&&(a=e)}}catch(f){var g=k[c].onError;g&&g(-1)}p=a}function e(a){for(var b in k){var c=
k[b].onError;c&&c(a)}}function m(a){return a&&(a=a.split(".",2),2==a.length)?a[0]:null}function f(a){return(a=k[a])?a.methods:null}function s(a,b){a.open("GET",b);a.onreadystatechange=function(){if(4==a.readyState)if(200!=a.status)e(a.status);else{var b=a.getResponseHeader("KL-Ajax-Response");if(b&&"1"==b){var c=a.getResponseHeader("KL-Kas-FunctionName");if(c&&c.length){var d=m(c);if(d&&(b=KasperskyLab.DecodeParameters(a),d=f(d))&&(c=d[c]))try{c(b)}catch(g){}}}else e(-1)}};a.send(null)}var r="/"+
a+"/"+g+"/from",k={},p=KasperskyLab.MaxRequestDelay,n=null,l=null;this.RegisterMethod=function(a,b){var c=m(a);if(c)if(c=f(c)){if(c[a])throw"Already registered";c[a]=b}else throw"Cannot registered";};this.UnregisterMethod=function(a){var b=m(a);b&&(b=f(b))&&delete b[a]};this.RegisterPlugin=function(a,b,f){if(k[a])throw"Already started";var g={onError:null,onPing:null,methods:{}};k[a]=g;g.onError=f;g.onPing=b;null==n&&(d(),c()||(n=setTimeout(function u(){try{d(),c()||(l=l||KasperskyLab.GetXmlHttp(),
s(l,r),n=setTimeout(u,p))}catch(a){e(-1)}},p)))};this.UnregisterPlugin=function(a){delete k[a];c()&&b()};this.UnregisterAll=function(){0!=k.length&&(b(),k={})};this.IsEmpty=c};return a}(KasperskyLab||{}),KasperskyLab=function(a){a.AjaxSession=function(a,g){var b=new KasperskyLab.CallReceiver(a,g);this.GetAjaxId=function(){return a};this.GetSessionId=function(){return g};this.ActivatePlugin=function(a,d,e){b.IsEmpty();b.RegisterPlugin(a,d,function(a){e&&e(a);if(b.IsEmpty())try{b.UnregisterAll()}catch(c){}})};
this.DeactivatePlugin=function(a){b.UnregisterPlugin(a);if(b.IsEmpty())try{b.UnregisterAll()}catch(d){}};this.RegisterMethod=function(a,d){b.RegisterMethod(a,d)};this.UnregisterMethod=function(a){b.UnregisterMethod(a)}};return a}(KasperskyLab||{});
KasperskyLab.SessionInstance = new KasperskyLab.AjaxSession('2A311594-1C24-9848-9F4B-1B4659FD94DD', 'D0395E4D-2FD7-694A-834F-71C54A8C1D18');var KasperskyLab=function(c){c.AntiBannerInstance=null;c.AntiBanner=function(d,c){function m(a,b){var c=a.attributes.getNamedItem(b);if(null==c||"on"!=c.value)a.setAttribute(b,"on"),KasperskyLab.AddEventListener(a,"mouseover",function(a){n(a.target||a.srcElement)}),KasperskyLab.AddEventListener(a,"mouseout",p),KasperskyLab.AddEventListener(a,"mousemove",q)}function n(a){e=a.src;f=!0;g&&h&&h.ShowBalloon(function(){return{x:k,y:l,isNeed:f}},5E3,1500)}function p(){f=!1}function q(a){k=a.clientX;l=a.clientY}
var r=new KasperskyLab.CallSender(d.GetAjaxId(),d.GetSessionId()),e=0,k=0,l=0,f=!1,g="Enabled"==c;d.ActivatePlugin("ab",function(){return KasperskyLab.MaxRequestDelay});d.RegisterMethod("ab.setstate",function(a){g=a.length&&"Enabled"==a[0]});KasperskyLab.AddStyles(['.kisb .kl_abmenu { font-size:12px; font-family: "Segoe UI", Arial, sans-serif; color: #FFFFFF; float: left; padding: 8px; border: 1px solid #FFFFFF; background: #057662; background: -moz-linear-gradient(#057662, #1a8171);background: -ms-linear-gradient(#057662, #1a8171);background: -webkit-gradient(linear, left top, left bottom, color-stop(0%, #057662), color-stop(100%, #1a8171)); background: -webkit-linear-gradient(#057662, #1a8171); background: -o-linear-gradient(#057662, #1a8171);filter: progid:DXImageTransform.Microsoft.gradient(startColorstr="#057662", endColorstr="#1a8171"); -ms-filter: "progid:DXImageTransform.Microsoft.gradient(startColorstr="#057662", endColorstr="#1a8171")";background: linear-gradient(#057662, #1a8171);border-radius: 8px;}']);
var h=new KasperskyLab.Balloon("ab",1,function(a){var b=document.createElement("div");b.className="kl_abmenu";b.appendChild(document.createTextNode("バナー広告対策でブロック"));a.appendChild(b)},function(){g&&e&&r.Call("ab.AddToBlockList",[e],function(a){0!=a&&alert("Cannot add url: "+e)});return!0});this.ActivateAntiBanner=function(){if(window.document)for(var a=window.document.getElementsByTagName("img"),b=0;b<a.length;++b)m(a[b],"KasperskyLab_AntiBanner")}};return c}(KasperskyLab||{});
KasperskyLab.AddEventListener(window,"load",function(){KasperskyLab.AntiBannerInstance||(KasperskyLab.AntiBannerInstance=new KasperskyLab.AntiBanner(KasperskyLab.SessionInstance,"Enabled"),KasperskyLab.AntiBannerInstance.ActivateAntiBanner())});

var KasperskyLab = (function (ns) { ns.DefaultUrlAdvisorEnable = true; ns.DefaultUrlAdvisorState = 'Enabled'; ns.DefaultUrlAdvisorMode = 1; ns.DefaultUrlAdvisorTermsUrl = 'http://redirect.kaspersky.com?target=threatcatterms&act-local=ja-JP&rpe=1'; ns.DefaultUrlAdvisorInfoUrl = 'http://redirect.kaspersky.com?target=threatcatinfo&act-local=ja-JP&act-pcid={2A6CC183-CFAF-4D47-8080-3077D1B0085F}&act-lic-type=5&act-lic-status=1&act-lic-lifespan=1095&act-lic-daystillexpiration=160&act-pid=kis&act-pv=15.0.1.415&ppcs-id=0&act-ksn=1'; return ns;} (KasperskyLab || {}));
var KasperskyLab = (function (ns) {

ns.UrlAdvisorBalloon = function ()
{
    var threatTypes = [
		{name:'Unknown', bit:-1},
		{name:'フィッシングリソース', bit:62},
		{name:'危険なリソース', bit:63}
	];
	var ratingIds = [
        {headerClass:'kl_header green', headerNode:'安全な Web サイト', textNode:'安全な Web サイト(KSN の情報)', marker:'kl_marker allow'},
        {headerClass:'kl_header grey', headerNode:'不明な Web サイト', textNode:'Web リソースの安全性に関する情報がありません(KSN の情報)', marker:'kl_marker unknown'},
        {headerClass:'kl_header red', headerNode:'危険な Web サイト', textNode:'危険な Web サイト(KSN の情報)', marker:'kl_marker disallow'}
    ];

    function GetImageSrc(imageName)
    {
        return KasperskyLab.GetResourceSrc('/ua/' + imageName);
    }

    function AddStyles()
	{
        KasperskyLab.AddStyles([
			'.kisb * { position: relative; display:block; overflow-x:hidden; width: auto; margin:0; padding:0; font-family: Verdana; line-height: 150%; text-indent:0; border:0; box-sizing:content-box; color:#000000; letter-spacing: normal; text-align: left; direction: ltr;}',
            '.kisb { z-index:10000; width: 280px; cursor:default; display:block;}',
            '.kisb .kl_header { padding:27px 26px 10px 26px;  }',
            '.kisb .kl_header.red { background-image:url(' + GetImageSrc('header_red.png') + ');}',
            '.kisb .kl_header.grey { background-image:url(' + GetImageSrc('header_grey.png') + ');}',
            '.kisb .kl_header.green { background-image:url(' + GetImageSrc('header_green.png') + ');}',
            '.kisb .kl_content { background: url(' + GetImageSrc('content.png') + ') repeat-y top left; padding:10px 26px 10px 26px;}',
            '.kisb .kl_content .block { width: 228px!important; }',
            '.kisb .kl_marker { margin-top: 5px; margin-bottom:10px; padding-top:2px; padding-left:25px; background-position-x: 0; background-position-y: 0; background-repeat: no-repeat; word-wrap: break-word;}',
            '.kisb .kl_marker.allow { background-image: url( ' + GetImageSrc('allow.png') + ')}',
            '.kisb .kl_marker.disallow { background-image: url(' + GetImageSrc('disallow.png') + ')}',
            '.kisb .kl_marker.unknown { background-image: url(' + GetImageSrc('unknown.png') + ')}',
			'.kisb .kl_tag { display:inline-block; background: left top url(' + GetImageSrc('tag.png') + ') no-repeat; padding-left:12px; padding-right:5px; margin-right:5px; margin-bottom:5px; font-size: 7.5pt;}',
            '.kisb .kl_external { margin-top: 15px; padding-top:2px; padding-left:20px; background-position-x: left; background-position-y: top; background-repeat: no-repeat;}',
            '.kisb .kl_external { background-image: url(' + GetImageSrc('external.png') + ')}',
            '.kisb .kl_footer { background: url(' + GetImageSrc('footer.png') + ') no-repeat bottom left; padding:6px 26px 22px 26px;}',
            '.kisb .kl_content * { font-size:8pt; }',
            '.kisb a { text-decoration: underline; display:inline-block; }',
            '.kisb a:hover { text-decoration: none; }',
            '.kisb a, .kisb a:link, .kisb a:hover, .kisb a:visited { color: #008ccc;}',
            '.kisb .kl_header { font-size:12pt; color: #ffffff;  }',
            '.kisb .kl_footer a { font-size:8pt; color: #4d4d4d; text-decoration:underline; }'
        ]);
	}
	
	function FixBigInt(bigInt)
	{
		if (bigInt.low >= 10000000000)
		{
			var addedHigh = Math.floor(bigInt.low / 10000000000);
			bigInt.low = bigInt.low % 10000000000;
			bigInt.high += addedHigh;
		}
	}
	
    /**
     * @return {string}
     */
	function BigIntToString(bigInt)
	{
		var result = '';
		if (bigInt.high)
		{
			result += bigInt.high;
			for (var i = bigInt.low.toString().length; i < 10; ++i)
				result += '0';
		}
		result += bigInt.low;
		return result;
	}
	
	/**
	 * @return {object}
	 */
	function GetMask(bit)
	{
		if (bit < 0 || bit >= 64)
			return {high: 0, low: 0};

		var mask = {
			high: 0,
			low: Math.pow(2, Math.min(50, bit))
		};
		FixBigInt(mask);
		
		if (bit > 50)
		{
			mask.low *= Math.pow(2, bit - 50);
			mask.high *= Math.pow(2, bit - 50);
			FixBigInt(mask);
		}

		return mask;
	}
	
	/**
	 * @return {string}
	 */
	function GetCategoriesMask(threats, categories)
	{
		var mask = {high: 0, low: 0},
			bits = [],
			i, count;
		if (threats)
			for (i = 0, count = threats.length; i < count; ++i)
				bits.push(threatTypes[threats[i]].bit);
		if (categories)
			for (i = 0, count = categories.length; i < count; ++i)
				bits.push(categories[i] - 1);
		for (i = 0, count = bits.length; i < count; ++i)
		{
			var addingMask = GetMask(bits[i]);
			mask.high += addingMask.high;
			mask.low += addingMask.low;
			FixBigInt(mask);
		}
		return BigIntToString(mask);
	}
	
    /**
     * @return {string}
     */
	function ConvertCategory(category)
	{
		if (category === 1 )
return 'アダルト';
else if (category === 2 )
return 'ソフトウェア、音楽、映像';
else if (category === 3 )
return 'アルコール、タバコ、麻薬';
else if (category === 4 )
return '暴力';
else if (category === 5 )
return '過激な表現、わいせつな表現';
else if (category === 6 )
return '武器、爆発物、花火';
else if (category === 7 )
return 'ギャンブル、宝くじ';
else if (category === 8 )
return 'インターネットコミュニケーション';
else if (category === 9 )
return 'インターネットコミュニケーション';
else if (category === 10 )
return '電子商取引';
else if (category === 11 )
return 'インターネットコミュニケーション';
else if (category === 12 )
return '求人サイト';
else if (category === 13 )
return 'HTTP クエリのリダイレクト';
else if (category === 14 )
return '電子商取引';
else if (category === 15 )
return 'コンピューターゲーム';
else if (category === 16 )
return '決済システム';
else if (category === 17 )
return '銀行 Web サイト';
else if (category === 18 )
return '差別';
else if (category === 19 )
return '不満';
else if (category === 20 )
return '独自の決済システムを持つオンラインストア';
else if (category === 21 )
return '警察機関指定の危険サイト';
else if (category === 22 )
return 'ソフトウェア、音楽、映像、および関連コンテンツ';
else if (category === 27 )
return 'ギャンブル、宝くじ';
else if (category === 28 )
return 'インターネット上のコミュニケーション';
else if (category === 34 )
return 'オンライン上の商取引';
else if (category === 35 )
return 'コンピューターゲーム';
else if (category === 36 )
return '宗教';
else if (category === 37 )
return 'ニュース';
else return 'Unknown';
	}

    /**
     * @return {string}
     */
    function ConvertThreat(threat)
	{
        return threatTypes[threat].name;
	}

	function AddTagsFromList(parentElement, list, converter)
	{
		if (!list)
			return;
		for (var i = 0, count = list.length; i < count; ++i)
		{
			var spanElement = document.createElement('span');
			spanElement.className = 'kl_tag';
			spanElement.appendChild(document.createTextNode(converter(list[i])));
			parentElement.appendChild(spanElement);
		}
	}
	
	function AddVerdictTags(parentElement, verdict)
	{
		if ((!verdict.categories || verdict.categories.length == 0) && (!verdict.threats || verdict.threats.length == 0))
			return;

		parentElement.appendChild(document.createElement('br'));
		parentElement.appendChild(document.createElement('br'));
		parentElement.appendChild(document.createTextNode('カテゴリ: '));
		
		var divElement = parentElement.appendChild(document.createElement('div'));
		AddTagsFromList(divElement, verdict.categories, ConvertCategory);
		AddTagsFromList(divElement, verdict.threats, ConvertThreat);
	}
	
	function RemoveAllChilds(element)
	{
		while (element.childNodes.length > 0)
			element.removeChild(element.childNodes[0]);
	}
	
	function UpdateBalloon(verdict, additionalInfoLink, termsLink)
	{
		var headerElement = document.getElementById('balloon_header');
		var contentElement = document.getElementById('balloon_content');
		var markerElement = document.getElementById('balloon_marker');
		var tagElement = document.getElementById('balloon_tags');
		var externalElement = document.getElementById('balloon_external');
		var termsElement = document.getElementById('balloon_terms');
		
		RemoveAllChilds(headerElement);
		RemoveAllChilds(contentElement);
		RemoveAllChilds(markerElement);
		RemoveAllChilds(tagElement);

        headerElement.className = ratingIds[verdict.rating-1].headerClass;
        headerElement.appendChild(document.createTextNode(ratingIds[verdict.rating-1].headerNode));
        contentElement
            .appendChild(document.createElement('b'))
            .appendChild(document.createTextNode(ratingIds[verdict.rating-1].textNode));
        markerElement.className = ratingIds[verdict.rating-1].marker;
		markerElement.appendChild(document.createTextNode(verdict.url));

		AddVerdictTags(tagElement, verdict);
		
		externalElement.href = additionalInfoLink + '&act-exturl=' + verdict.url + '&act-threat-cat=' + (verdict.rating - 1) + '&act-content-cat=' + GetCategoriesMask(verdict.threats, verdict.categories) + '&rpe=1';
		termsElement.href = termsLink;
	}
	
	function CheckMouseOverBalloon(mouseArgs)
	{
		if (m_balloon)
		{
			mouseArgs = mouseArgs || event;
			var rect = m_balloon.getBoundingClientRect();
			if (mouseArgs.clientX > rect.left &&
				mouseArgs.clientX < rect.right &&
				mouseArgs.clientY > rect.top &&
				mouseArgs.clientY < rect.bottom)
			{
				return;
			}
			HideBalloon();
		}
	}

	function CreateHeaderDiv(balloonDiv)
	{
		var headerDiv = document.createElement('div');
		headerDiv.id = 'balloon_header';
		
		balloonDiv.appendChild(headerDiv);
	}
	
	function CreateContentDiv(balloonDiv)
	{
		var contentDiv = document.createElement('div');
		contentDiv.className = 'kl_content';
		var blockDiv = document.createElement('div');
		blockDiv.className = 'block';
		contentDiv.appendChild(blockDiv);
		var contentTypeDiv = document.createElement('div');
		contentTypeDiv.className = 'block';
		contentTypeDiv.id = 'balloon_content';
		blockDiv.appendChild(contentTypeDiv);
		var markerDiv = document.createElement('div');
		markerDiv.className = 'kl_marker allow';
		markerDiv.id = 'balloon_marker';
		blockDiv.appendChild(markerDiv);
		var tagsDiv = document.createElement('div');
		tagsDiv.id = 'balloon_tags';
		blockDiv.appendChild(tagsDiv);
		var infoLink = document.createElement('a');
		infoLink.href = '#';
		infoLink.id = 'balloon_external';
		infoLink.className = 'kl_external';
		infoLink.target = '_blank';
		infoLink.appendChild(document.createTextNode('詳細情報'));
		blockDiv.appendChild(infoLink);
		
		balloonDiv.appendChild(contentDiv);
	}
	
	function CreateFooterDiv(balloonDiv)
	{
		var footerDiv = document.createElement('div');
		footerDiv.className = 'kl_footer';
		footerDiv.id = 'balloon_footer';
		var termsLink = document.createElement('a');
		termsLink.id = 'balloon_terms';
		termsLink.target = '_blank';
		termsLink.appendChild(document.createTextNode('利用規約'));
		// TODO: add terms onclick like in previous version
		footerDiv.appendChild(termsLink);
		
		balloonDiv.appendChild(footerDiv);
	}
	
	function CreateBalloon()
	{
		AddStyles();
	
		var balloonDiv = document.createElement('div');
		balloonDiv.className = 'kisb';
		balloonDiv.id = 'balloon_parent_div';
		balloonDiv.onmouseout = CheckMouseOverBalloon;
		
		CreateHeaderDiv(balloonDiv);
		CreateContentDiv(balloonDiv);
		CreateFooterDiv(balloonDiv);
		
		balloonDiv.style.visibility = 'hidden';
		document.body.appendChild(balloonDiv);
		return balloonDiv;
	}

	var m_balloon = null;

	function GetElementSize(element)
	{
		var rect = element.getBoundingClientRect();
        var width = rect.width ? rect.width : rect.right - rect.left;
        var height = rect.height ? rect.height : rect.bottom - rect.top;
			
		return {width: width, height: height};
	}
	
	this.ShowBalloon = function(clientX, clientY, verdict, additionalInfoLink, termsLink)
	{
		m_balloon = document.getElementById('balloon_parent_div');
		if (!m_balloon)
			m_balloon = CreateBalloon();
		UpdateBalloon(verdict, additionalInfoLink, termsLink);
		
		var clientWidth = document.documentElement.clientWidth || document.body.clientWidth;
		var balloonSize = GetElementSize(m_balloon);
		var halfWidth = balloonSize.width / 2;
		var x;
		if (halfWidth > clientX)
			x = 0;
		else if (halfWidth + clientX > clientWidth)
			x = clientWidth - balloonSize.width;
		else
			x = clientX - halfWidth;
		
		var clientHeight = document.documentElement.clientHeight || document.body.clientHeight;
		var y = (clientY + balloonSize.height > clientHeight) ? clientY - balloonSize.height : clientY;
		if (y < 0)
			y = 0;

		var top = (document.documentElement && document.documentElement.scrollTop) || document.body.scrollTop;
		y += top;
		var left = (document.documentElement && document.documentElement.scrollLeft) || document.body.scrollLeft;
		x += left;

		m_balloon.style.position = 'absolute';
		m_balloon.style.top = Math.round(y).toString() + 'px';
		m_balloon.style.left = Math.round(x).toString() + 'px';
		m_balloon.style.visibility = 'visible';
	}
	
	function HideBalloon()
	{
		if (m_balloon)
			m_balloon.style.visibility = 'hidden';
	}
};

return ns;
} (KasperskyLab || {}));
var KasperskyLab = (function (ns) {

ns.UrlAdvisorInstance = null;

ns.UrlAdvisor = function (session)
{
    var that = this;
	var imgDanger = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAQCAYAAAGHNqTJAAAACXBIWXMAAA7DAAAOwwHHb6hkAAACo0lEQVR4nIVTTUgVURT+7n2jps9yZp6WpmZpVphiGC0SKigwQVq0SZCkVS0MXFhRQQt3LgItoiQLDMldIWhWSIhQixbRU8envWwRZfr8eb4Rez+KM7c71/H5Jow+OHPvPffMOd/57r0EHN0qYYSxOrQrrqHAnWusXaGMNAO0WCWGdFQhhlp0AMSK9e1OY+knTiOl+CBeP2xddz7g8bBh8Bmxsy7yQbHmrk6VzlQ1NGXl7cqB/HUCUiZj2dbOwtwsflm/3FelasrMNxt5yMZkoHwvO/x7CaYeQnwzNQ2DkSikDhlHKsrKvVHfKFwNTTBCi0hWVAQG+rH8zY8Vnppe0THsHdPw3Sap86CRt33IrqoRvhVeLF6uVaZdEaA+3pDNJRVYjAd1q7jO3XfhRFB8uzy0ZeHqJfbTA4cF6s4xdMqQJ2prmMY1t6TWPFSMMzcbhY88z003CqJhamUq5h0x0wQhBJPtbSI7dXPTOTvdZkgoxYz3E4ycXOGjU5HIE91q02b17lEbMktKceh8rfCJLu7J1HARUGwBSYikm0luHhT7azMl8WwsNPOS+xX6LLewsL7iwkUk7cjYKqmAEQljvK8H/tHPm2J2qqh2u7f3V545S6P9PTzK+GeCDZBtqfgQi60zearQjqKS0svqUgir01MiIJ9LZyEy6cfq/CzkypNizUwDC696EJv6IdYjXDHpsUKGikrLThlffJhLqJ5vj2n8sltmYfr9IILasLMtSzQDrNE/pnlVMOoQKAGBcQ1rnHYef0FZx44jPD8PrfeF2FvjzUgNIYy2yaYnQOhEClh24vkEeWsfe1/C5AwV/o6SPZnYWbAPcv6e+FlbTBzFWzNoCyO4Zf5X0k24uDkuRtOSeXtZN12M4QZfhrb+zYGgSUjdHytwCP1xLDmyAAAAAElFTkSuQmCC';
	var imgSuspicious = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAQCAYAAAGHNqTJAAAACXBIWXMAAA7DAAAOwwHHb6hkAAACtElEQVR4nIVTz08TQRT+drcL0qUU2P4GjbIFGoNBsQlH4k3/BROOnog9iAdCL9w49MSBi5LQeODAwXioChoDiQejHFCBUKSWSoV2S3/Qpt020h/ObKHQAPolkzfz5nvvzftmhgGBz+erMAzzkPF4PMvBYHBIkiQwExMTrNPpLLF2yVIKBNbBUO67hbnKl5VN7O3HMTg4CA11bmzuQdfSCgcZfr+/yiRZk8S00Tnn9XojS0tLxvThAa516sBquIKF7jQ2NiKRzIFd3wg9cDjsEJp1qkPNQbG46KsITUcoFv+cuMByHKJyGcz09PTt3m7baiaTwvsPKxCEK8jlCrjVJ8Fibkc0VgA7MjLy9dvatpqWgud5dN3oxNr6T9UXj8dPy7lcrhdms2mYIyVOUC6XEY3KyRqJ9PaUGA/qkVDVmJ+fn5S6jGNyNFS32y7aRG52drbVLll90UgIL199JOewqXbrRxgWUzM05XIpsb/3qxble/MJDCl8b2gA+fwRNBquzCr5Yo1QqVTQ0WEieqTQ0iKA3Q3LzymTDoqBOzchywnSbkD1qV243eMlk0lkcQE0VZEa+HA4UjIYxLrNVOrwVCwK+k76+/u9er12WOq6qqp7GYqlIsK7EcQO0qdizs3N3ed57nWP3cbG47/Vhv4HluUQkYvVk8zMzDyzWtsf8XwRhbyiEt4ufFat1SpCT1Txb+0eBzJw3u2FKOrVtRwjkk5NTS2bTfqhXDZ5YfVIJKEOim77VSK3UZ2fKKwoCjTZbNa16Q+uGgwCyzDMuSQURmMbvUBsB8LYCe1Dq22Cw3G9loR1u93fFSUv7uzI0XRawdl7FIQm9PX1wGIxkUAtdDqBfIoSMplsjUeT1JUeHR2dbGjgx0SxDZed6iyqT/0A55j0mmOx2BOizziOv/U/kCDFHv8FtZovvL2puagAAAAASUVORK5CYII=';
	var imgGood = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAQCAYAAAGHNqTJAAAACXBIWXMAAA7DAAAOwwHHb6hkAAACr0lEQVR4nH1TS0xTQRQ9M320r7U/CoGilCCIWB4KXcjChV24wS1xRcLSpS6MJsQVK0ggoC7c6Mboho3iJ6CJG6KJ0RWihj/StCnFSin2S9v33jjv9QME8SSTO3Pn3M/ce4eA4/6MxBhBPxl9Ic3KedUvGAnI0BCos0dShPa+80o6wUA07suVyyy0sYtkvACThYBqyt2dMByuFBpbc8jvlZjc6w4X1dqejr+WIpmEWq0ZeFqtoCebqVu7qTKqyOcyoIEl9apmb3VkUciliz40PPvUy1wNBAU1WVbBQESsLkQgjE5J3V0XOuf+5FYx/yULo4lwdwzuJiOszgxUuZTNw/de5qhhCK4QWKyAxc6wvUnQdJYh/JPuhxue9D6ta0wPGAysEk5VCX6FTuxUSA9mOm8zsDEcRkwnTLyRRvw9/YOh1NtDt3XiJZB7U91OX5c/Hit8xvJcAu0+uy4pJWjrskEwmoVYdO9jxWrla0KXLZ0iFKUAwe4iVJELFQLjeTpqKNKJPEStI5vB1GONUCZpT0zuqogEFF2nJzn6/JzibspT/AO6MvN9qSoaFlD2VF6xLcN+sTRoc+K4KD2pqzk94Gvrg0mw/cupjoKSxWLwHQLh+f1iTkxLvWKVddonXaFbmQ9gUI91UIaBmLC+GC1mMv7K+6jZI10X7Rlk5WipbGld2qoFiGaK35t5/Uy4xakWERabQT8HljMQxqak2TMtXn+OriO1dzR6Mi7zVdzXNhh4uTVjldejyGVc8EqRm2sbC3NuDyghR3wUs3Hy6nLb7YiCeFSBUQTqPUWyyp3QO9d+fKOKsSa0hq1sSsbBPprMjP8wGc5amT9J4c1mfCKALH9pmadlcij28GTHiMmsDLrqczguq4PQRz0o4ghVa7OxveMWH/u7KH3r/yDGGLvxF30tKs+p7Df9AAAAAElFTkSuQmCC';
   
	var m_caller = new KasperskyLab.CallSender(session.GetAjaxId(), session.GetSessionId());
	var m_urlAdvisorBalloon = new KasperskyLab.UrlAdvisorBalloon();

    var m_settingsEnabled = KasperskyLab.DefaultUrlAdvisorEnable;
	var m_enabled = m_settingsEnabled && (KasperskyLab.DefaultUrlAdvisorState == 'Enabled');
	var m_checkOnlySearchResults = KasperskyLab.DefaultUrlAdvisorMode;
	var m_additionalInfoUrl = KasperskyLab.DefaultUrlAdvisorInfoUrl;
	var m_termsUrl = KasperskyLab.DefaultUrlAdvisorTermsUrl;
	var m_postponeCategorizeStarted = false;
    var m_urlCategorizeRequestTime = 0;
	var m_state = KasperskyLab.DefaultUrlAdvisorState;
    
	session.ActivatePlugin('ua', OnPing);
	session.RegisterMethod('ua.verdict', SetVerdict);
	session.RegisterMethod('ua.settings', SetSettings);
	session.RegisterMethod('ua.state', SetState);

	/**
	* @return {number}
	*/
    function OnPing(currentTime)
	{
       var timeFormRequest = (currentTime >= m_urlCategorizeRequestTime) ? currentTime - m_urlCategorizeRequestTime : 0;
       
       return timeFormRequest <= 10000 ? 500 : KasperskyLab.MaxRequestDelay;
	}

    /**
     * @return {boolean}
     */
    function IsLinkHighlighted(linkElement)
	{
		var nextElement = linkElement.nextSibling;
		return nextElement !== null && nextElement.name === 'KavHltTag';
	}
	
	function GetLinkIcon(linkElement)
	{
		if (!IsLinkHighlighted(linkElement))
		{
			var icon = document.createElement('img');
			icon.name = 'KavHltTag';
			icon.width = 12;
			icon.height = 12;
			linkElement.parentNode.insertBefore(icon, linkElement.nextSibling);
		}
		return linkElement.nextSibling;
	}
	
	function UpdateIconImage(icon, verdict)
	{
		if (verdict.rating === 1)
		{
			icon.src = imgGood;
			icon.setAttribute('kis_status', '16');
		}
		else if (verdict.rating === 2)
		{
			icon.src = imgSuspicious;
			icon.setAttribute('kis_status', '8');
		}
		else if (verdict.rating === 3)
		{
			icon.src = imgDanger;
			icon.setAttribute('kis_status', '4');
		}
	}
	
	function SubscribeIconOnMouseEvents(icon, verdict)
	{
		var balloonTimerId = 0;
		icon.onmouseout = function()
		{
			if (balloonTimerId)
			{
				window.clearTimeout(balloonTimerId);
				balloonTimerId = 0;
			}
		};
		icon.onmouseover = function(mouseArgs)
		{
			if (!balloonTimerId)
			{
				mouseArgs = mouseArgs || event;
				balloonTimerId = window.setTimeout(function(clientX, clientY)
					{
						return function()
						{
							m_urlAdvisorBalloon.ShowBalloon(clientX, clientY, verdict, m_additionalInfoUrl, m_termsUrl);
						}
					}(mouseArgs.clientX, mouseArgs.clientY),
					300);
			}
		};
	}
	
	function SetVerdict(argumentsList)
	{
		for (var currentVerdict = 0; currentVerdict < argumentsList.length; currentVerdict++)
		{
			var verdict = KasperskyLab.JSONParse(argumentsList[currentVerdict]);
			for (var currentLinkIndex = 0; currentLinkIndex < document.links.length; currentLinkIndex++)
			{
				var linkElement = document.links[currentLinkIndex];
				if (verdict.url === linkElement.getAttribute('href') && (!m_checkOnlySearchResults || IsLinkSearchResult(linkElement)))
				{
					var icon = GetLinkIcon(linkElement);
					UpdateIconImage(icon, verdict);
					SubscribeIconOnMouseEvents(icon, verdict);
				}
			}
		}
	}

	function SetSettingsImpl(argumentList)
	{
		if (argumentList.length > 0)
	    {
			m_settingsEnabled = (argumentList[0] != '0');
			m_enabled = m_settingsEnabled && (m_state == 'Enabled');
	 	}

		if (!m_enabled)
			return;

		m_checkOnlySearchResults = !!(argumentList.length > 1 && argumentList[1] == 1);
		
		if (argumentList.length > 2)
			m_termsUrl = argumentList[2];
			
		if (argumentList.length > 3)
			m_additionalInfoUrl = argumentList[3];
	}

	
	function ClearImages()
	{
		var images = document.getElementsByName('KavHltTag');
		while (images.length > 0)
			images[0].parentNode.removeChild(images[0]);
	}	

	
	function SetSettings(argumentList)
	{
		ClearImages();
		SetSettingsImpl(argumentList);
		CategorizeUrl();
	}

	function SetState(argumentList)
	{
		if (argumentList.length > 0)
		{
			ClearImages();	
			m_state = argumentList[0];
			m_enabled = m_settingsEnabled && (m_state == 'Enabled');
			CategorizeUrl();
		}
	}
	
	function IsLinkSearchResult(linkElement)
	{
		return false;
	}
	
	function IsNeedCategorizeLink(linkElement)
	{
		return !IsLinkHighlighted(linkElement) &&
			(!m_checkOnlySearchResults || IsLinkSearchResult(linkElement)) &&
			linkElement.id !== 'balloon_external' &&
			linkElement.id !== 'balloon_terms';
	}

    /**
     * @return {boolean}
     */
    function IsLinkListChanged()
	{
		for (var i = 0; i < document.links.length; i++) {
            var link = document.links[i];
            if (!link.getAttribute('sended') && IsNeedCategorizeLink(link))
                return true;
        }

		return false;
	}

    /**
     * @return {boolean}
     */
    function IsElementLink(element)
	{
		return element.nodeType == 1 && element.nodeName.toLowerCase() == 'a';
	}
	
	function NodeRemove(element)
	{
		if (IsElementLink(element) && IsLinkHighlighted(element))
		{
			element.parentNode.removeChild(element.nextSibling);
		}
		else
		{
			for (var i = 0; i < element.childNodes.length; ++i)
				NodeRemove(element.childNodes[i])
		}
	}
	
	function PostponeCategorize()
	{
		setTimeout(CategorizeUrl, 500);
		m_postponeCategorizeStarted = true;
	}
	
	function NodeInsert(element)
	{
		if (m_postponeCategorizeStarted)
			return;
		
		if (IsElementLink(element))
		{
			PostponeCategorize();
		}
		else
		{
			for (var i = 0; i < element.childNodes.length; ++i)
				NodeInsert(element.childNodes[i]);
		}
	}
	
	function CategorizeUrl()
	{
		if (!m_enabled)
			return;
			
		m_postponeCategorizeStarted = false;
		
		var linksForCategorize = [];
		for (var i = 0; i < document.links.length; i++)
		{
			if (IsNeedCategorizeLink(document.links[i]))
			{
				linksForCategorize.push(document.links[i].getAttribute('href'));
				document.links[i].setAttribute('sended', "true");
			}
		}
		m_caller.Call('ua.categorize', linksForCategorize);
        m_urlCategorizeRequestTime = KasperskyLab.GetCurrentTime();
	}

	this.RunWithTimeoutChangeChecker = function()
	{
		if (IsLinkListChanged())
			CategorizeUrl();
		
		setTimeout(that.RunWithTimeoutChangeChecker, 10 * 1000);
	};
	
	this.RunWithDomChangeListeners = function()
	{
		CategorizeUrl();
		window.addEventListener("DOMNodeInserted", function(event){NodeInsert(event.target);});
		window.addEventListener("DOMNodeRemoved", function(event){NodeRemove(event.target);});
	};
};

return ns;
} (KasperskyLab || {}));

KasperskyLab.AddEventListener(window, "load", function () {
    if (!KasperskyLab.UrlAdvisorInstance) {
        KasperskyLab.UrlAdvisorInstance = new KasperskyLab.UrlAdvisor(KasperskyLab.SessionInstance);
        if ("addEventListener" in window){
            KasperskyLab.UrlAdvisorInstance.RunWithDomChangeListeners();
        } else {
            KasperskyLab.UrlAdvisorInstance.RunWithTimeoutChangeChecker();
        }
    }
});


 return KasperskyLab; })();