var vc_type = "";
var lastUin = 1;
var js_bgnrun_time = new Date();
var g_time = {};
var g_begTime = new Date();
try {
    g_time.time0 = _TIMER_1_;
    g_time.time1 = _TIMER_2_;
    g_time.time2 = g_time.time1;
    g_time.time3 = _TIMER_3_
} catch(e) {}
var isLoadVC = false;
var g_appid = 46000101;
var g_uin = 0;
var g_domain = "qq.com";
var g_target = "_top";
var g_https = false;
document.domain = "qq.com";
var first = true;
var changeimg = false;
var g_version = 10063002;
var login_param = "hide_title_bar=1";
function $(A) {
    return document.getElementById(A)
}
var f_u = $("u");
var f_p = $("p");
var f_v = $("verifycode");
var firstuin = "";
var isAbleSubmit = false;
var global = {};
global.flag2 = null;
global.domain = (window.location + "").replace(/(^((https|http)?:\/\/))/g, "").replace(/(([\/]{1}\S*)$)/g, "");
function checkFlag2() {
    if (global.domain.indexOf("t.qq.com") != -1) {
        global.flag2 = 2
    }
    if (global.domain.indexOf("qzone.qq.com") != -1) {
        global.flag2 = 3
    }
}
function ptui_notifySize(B) {
    try {
        obj = $(B);
        if (obj) {
            width = 1;
            height = 1;
            if (obj.offsetWidth > 0) {
                width = obj.offsetWidth
            }
            if (obj.offsetHeight > 0) {
                height = obj.offsetHeight
            }
            if (parent.ptlogin2_onResize) {
                parent.ptlogin2_onResize(width, height);
                window.scroll(0, 10)
            } else {
                frameElement.width = width;
                frameElement.style.width = width + "px";
                frameElement.height = height;
                frameElement.style.height = height + "px";
                frameElement.style.visibility = "hidden";
                frameElement.style.visibility = "visible"
            }
        }
    } catch(A) {}
}
var g_speedArray = new Array();
function ptui_setSpeed(B) {
    if (B <= 0) {
        return
    }
    var A = g_speedArray.length;
    g_speedArray[A] = new Array(B, new Date())
}
function ptui_check_qlogin() {
    if (!window.ActiveXObject) {
        return 0
    }
    try {
        var D = new ActiveXObject("SSOAxCtrlForPTLogin.SSOForPTLogin2");
        var F = D.CreateTXSSOData();
        D.InitSSOFPTCtrl(0, F);
        var E = D.CreateTXSSOData();
        var A = D.DoOperation(2, E);
        var B = A.GetArray("PTALIST");
        var C = B.GetSize();
        if (C > 0) {
            return C
        }
    } catch(G) {
        return 0
    }
    return 0
}
var xuiFrame = false;
var curXui = false;
var str2n = "使用其他号码登录";
var q_clock;
function qlogin_check() {
    q_clock = setInterval(qlogin_check.checking_qstatus, 200);
    qlogin_check.num = 50;
    document.cookie = "ptui_qstatus=1;domain=qq.com;path=/"
}
qlogin_check.checking_qstatus = function() {
    if (qlogin_check.num == 0) {
        switchpage()
    }
    if (document.cookie.indexOf("ptui_qstatus=2") > -1) {
        clearInterval(q_clock)
    }
    if (document.cookie.indexOf("ptui_qstatus=3") > -1) {
        clearInterval(q_clock);
        switchpage()
    }
    qlogin_check.num--
};
function loadxui(A) {
    if (xuiFrame) {
        $("qlogin").style.display = "block";
        return
    } else {
        var L = location.href.indexOf("?s_url=");
        var D = "http://t.qq.com";
        if (L > -1) {
            var B = location.href.indexOf("#");
            D = location.href.substring(L + 7, B)
        }
        var K, I, G, J;
        try {
            K = document.getElementsByName("u1")[0].value;
            I = document.getElementById("wording").value;
            G = document.getElementById("css").value;
            J = document.getElementsByName("ptredirect")[0].value
        } catch(H) {}
        var C = "http://xui.ptlogin2.qq.com/div/qlogin_div_t.html?flag2=" + global.flag2 + "&u1=" + encodeURIComponent(K);
        if (I) {
            C += "&wording=" + escape(I)
        }
        if (G) {
            C += "&css=" + encodeURIComponent(G)
        }
        if (J) {
            C += "&ptredirect=" + encodeURIComponent(J)
        }
        C += "&v=" + g_version + "#" + (g_begTime - 0);
        var F = $("qlogin");
        var E = 136;
        if (A > 5) {
            A = 5
        }
        E += 28 * (A - 1);
        if (F) {
            F.innerHTML = '<iframe id="xui" name="xui" allowtransparency="true" scrolling="no" frameborder="0" width="100%" height="' + E + '" src="' + C + '">';
            F.style.display = "block";
            $("web_login").style.display = "none"
        }
        curXui = true;
        xuiFrame = true;
        qlogin_check()
    }
}
function switchpage() {
    if (curXui) {
        $("web_login").style.display = "block";
        $("qlogin").style.display = "none";
        $("switch").innerHTML = '<a href="javascript:;" onclick="switchpage();return false;">切换到快速登录模式</a>';
        ptui_notifySize("login");
        if (typeof(ptui_initFocus) != "undefined") {
            ptui_initFocus($("loginform"))
        }
        curXui = false;
        clearInterval(q_clock)
    } else {
        $("qlogin").style.display = "block";
        $("web_login").style.display = "none";
        $("switch").innerHTML = '<a style="cursor:pointer;" onclick="switchpage();">' + str2n + "</a>";
        curXui = true;
        qlogin_check();
        ptui_notifySize("login")
    }
}
function onSelectLoad() {
    checkFlag2();
    var A = 0;
    if (document.cookie.toLowerCase().indexOf("pt_qlogincode=5") > -1) {
        A = 0
    } else {
        A = ptui_check_qlogin()
    }
    if (A > 0) {
        loadxui(A);
        if ($("label_unable_tips")) {
            $("label_unable_tips").innerHTML = ""
        }
        if ($("switch")) {
            $("switch").innerHTML = '<a style="cursor:pointer;" onclick="switchpage();">' + str2n + "</a>";
            $("switch").style.display = "block"
        }
        if (typeof callback == "function") {
            callback()
        }
    } else {
        if ($("label_unable_tips")) {
            $("label_unable_tips").innerHTML = ""
        }
        if ($("switch")) {
            $("switch").style.display = "none"
        }
    }
    ptui_setSpeed(1);
    ptui_notifySize("login")
}
function onPrePageLoad() {
    var B = $("loginform");
    if ($("low_login_enable")) {
        $("low_login_enable").onclick = function() {
            ptui_onEnableLLogin(B)
        }
    }
    ptui_onEnableLLogin(B);
    ptui_setDefUin(B, "");
    ptui_setSpeed(2);
    var A = 0;
    if (location.hash) {
        A = location.hash.substr(1, location.hash.length)
    }
    ptui_reportSpeed(g_begTime, A);
    g_time.time4 = new Date();
    webLoginReport();
    ptui_notifySize("login");
    if (!curXui) {
        ptui_initFocus(B)
    }
}
onSelectLoad();
try {
    var input_aid = $("aid").value
} catch(e) {}
var g_changeNum = 0;
var g_checkTime = 0;
var g_imgTime = 0;
function ptui_onEnableLLogin(B) {
    var A = B.low_login_enable;
    var C = B.low_login_hour;
    if (A != null && C != null) {
        C.disabled = !A.checked
    }
}
function ptui_setDefUin(C, B) {
    if (B == "" || B == null) {
        var A = getCookie("ptui_loginuin2");
        if (A) {
            B = A
        } else {
            B = getCookie("ptui_loginuin")
        }
        if (B) {
            firstuin = B
        }
    }
    if (B != "" && B != null) {
        f_u.value = B
    }
}
var g_xmlhttp;
var g_loadcheck = true;
var g_submitting = false;
function ptui_needVC(C, D) {
    if (input_aid == D) {
        if ((C.indexOf("@") < 0) && isNaN(C)) {
            C = "@" + C
        }
    }
    var B = "http://ptlogin2." + g_domain + "/check?uin=" + C + "&appid=" + D + "&r=" + Math.random();
    var A = document.createElement("script");
    g_checkTime = new Date() - 0;
    A.src = B;
    document.body.appendChild(A);
    g_loadcheck = true;
    return
}
function ptui_checkVC(A, B) {
    g_loadcheck = false;
    g_checkTime = new Date().getTime() - g_checkTime;
    if (g_submitting) {
        return
    }
    var D = new Date();
    if (firstuin != "" && g_changeNum <= 1) {
        g_time.time7 = D;
        var C = {
            "12": g_time.time7 - g_time.time6
        };
        if (firstuin != "") {
            C["16"] = g_time.time6 - g_time.time3,
            C["17"] = g_time.time7 - g_time.time3
        }
        if (!xuiFrame) {
            ptui_speedReport(C)
        }
    } else {
        g_time.time10 = D;
        var C = {
            "13": g_time.time10 - g_time.time9
        };
        ptui_speedReport(C)
    }
    if (A == "0") {
        f_v.value = B;
        loadVC(false)
    } else {
        vc_type = B;
        f_v.value = "";
        loadVC(true)
    }
}
function ptui_trim(A) {
    return A.replace(/(^\s*)|(\s*$)/g, "")
}
function ptui_checkQQUin(qquin) {
    if (qquin.length == 0) {
        return false
    }
    qquin = ptui_trim(qquin);
    if ((new RegExp(/^[a-zA-Z]{1}([a-zA-Z0-9]|[-_]){0,19}$/).test(qquin))) {
        if (input_aid == g_appid) {
            return true
        } else {
            $("u").value = ptui_trim($("u").value) + "@qq.com";
            qquin = $("u").value
        }
    }
    if (! (new RegExp(/^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/).test(qquin))) {
        if (qquin.length < 5 || qquin.length > 12 || parseInt(qquin) < 1000) {
            return false
        }
        var exp = eval("/^[0-9]*$/");
        return exp.test(qquin)
    }
    return true
}
function ptui_changeImg() {
    changeimg = true;
    var A = $("imgVerify");
    try {
        if (A != null) {
            var D = g_uin;
            if (isNaN(g_uin) && (g_uin.indexOf("@") < 0)) {
                D = "@" + g_uin
            }
            A.src = "http://captcha.qq.com/getimage?aid=" + input_aid + "&uin=" + D + "&" + Math.random() + "&vc_type=" + vc_type;
            var B = f_v;
            if (B != null && B.disabled == false) {
                B.focus();
                B.select()
            }
        }
    } catch(C) {}
}
function ptui_initFocus(A) {
    try {
        if (f_u.value == "") {
            f_u.focus();
            return
        }
        if (f_p.value == "") {
            f_p.focus();
            return
        }
        if (f_v.value == "") {
            f_v.focus()
        }
    } catch(B) {}
}
function getCookie(D) {
    var B = D + "=";
    var F = B.length;
    var A = document.cookie.length;
    var E = 0;
    while (E < A) {
        var C = E + F;
        if (document.cookie.substring(E, C) == B) {
            return getCookieVal(C)
        }
        E = document.cookie.indexOf(" ", E) + 1;
        if (E == 0) {
            break
        }
    }
    return null
}
function getCookieVal(B) {
    var A = document.cookie.indexOf(";", B);
    if (A == -1) {
        A = document.cookie.length
    }
    return unescape(document.cookie.substring(B, A))
}
function ajax_Submit() {
    if (!isLoadVC) {
        g_uin = 0
    }
    var D = true;
    var E = $("loginform");
    var B = "";
    for (var A = 0; A < E.length; A++) {
        if (E[A].name == "fp" || E[A].type == "submit") {
            continue
        }
        if (E[A].name == "low_login_enable" && (!E[A].checked)) {
            D = false;
            continue
        }
        if (E[A].name == "low_login_hour" && (!D)) {
            continue
        }
        B += E[A].name;
        B += "=";
        if (input_aid == g_appid && E[A].name == "u" && E[A].value.indexOf("@") < 0 && isNaN(E[A].value)) {
            B += "@" + E[A].value + "&";
            continue
        }
        if (E[A].name == "p") {
            var F = "";
            F += E.verifycode.value;
            F = F.toUpperCase();
            B += md5(md5_3(E.p.value) + F)
        } else {
            if (E[A].name == "u1" || E[A].name == "ep") {
                B += encodeURIComponent(E[A].value)
            } else {
                B += E[A].value
            }
        }
        B += "&"
    }
    B += "fp=loginerroralert";
    var C = document.createElement("script");
    C.charset = "UTF-8";
    C.src = "http://ptlogin2.qq.com/login?" + B;
    document.cookie = "login_param=" + encodeURIComponent(login_param) + ";domain=ui.ptlogin2." + g_domain + ";path=/";
    document.body.appendChild(C);
    return
}
var LOGIN_FAIL_ERRMSG = ["登录成功!", "系统繁忙，请稍后重试。", "已经过期的QQ号码。", "您输入的密码有误，请重试。", "您输入的验证码有误，请重试。", "校验失败。", "密码错误。如果您刚修改过密码, 请稍后再登录.", "您的输入有误, 请重试。", "您的IP输入错误的次数过多，请稍后再试。", "您输入的帐号不存在，请重试。", "您输入的帐号不正确，请重试。", "您输入的帐号不正确，请重试。", "已经过期的QQ号码。", "", "该QQ号码已经转换为Email帐号，请使用Email帐号登录。", "", "您的IP输入错误的次数过多，请稍后再试。", "", "您的Email帐号未进行验证，请验证后再登录。", "很抱歉，您的号码暂时不能登录，请联系客服中心。", "很抱歉，您的号码暂时不能登录，请联系客服中心(20)。"];
function ptuiCB(D, B, C, H) {
    g_time.time13 = new Date();
    var G = {
        "15": g_time.time13 - g_time.time12
    };
    ptui_speedReport(G);
    if (typeof(ptui_bos) != "undefined" && typeof(ptui_bos) == "function") {
        ptui_bos(D)
    }
    first = false;
    if (C != "" || D == 0) {
        var A = new Date();
        A.setHours(A.getHours() + 24 * 30);
        document.cookie = "ptui_loginuin2=" + escape(f_u.value) + ";expires =" + A.toGMTString() + ";domain=" + global.domain;
        if (C != "") {
            switch (H) {
            case "0":
                C += "&isdiv=1";
                f_p.value = "";
                $("web_login").style.display = "none";
                $("qlogin").style.display = "block";
                $("switch").style.display = "none";
                var E = $("qlogin");
                E.innerHTML = '<iframe id="mb" name="mb" allowtransparency="true" scrolling="no" frameborder="0" width="100%" height="300" min-height="300" src="' + C + '">';
                break;
            case "1":
                top.location.href = C;
                break;
            case "2":
                parent.location.href = C;
                break;
            default:
                top.location.href = C
            }
            return
        }
        return
    }
    g_submitting = false;
    if (B == 0) {
        if (typeof(LOGIN_FAIL_ERRMSG[D]) != "undefined") {
            alert(LOGIN_FAIL_ERRMSG[D])
        } else {
            alert("系统繁忙")
        }
    } else {
        alert("登录失败，请重试!");
        f_p.value = "";
        f_p.focus();
        f_p.select()
    }
    if (isLoadVC) {
        ptui_changeImg();
        f_v.value = "";
        loadVC(true);
        f_v.focus();
        f_v.select()
    }
    if (D == 3 || D == 4) {
        if (navigator.userAgent.toLowerCase().indexOf("webkit") > -1) {
            f_u.focus()
        }
        if (D == 3) {
            f_p.value = ""
        }
        f_p.focus();
        f_p.select();
        if (D == 4) {
            try {
                f_v.focus();
                f_v.select()
            } catch(F) {}
        }
        if (B != 0) {
            f_v.value = "";
            loadVC(true);
            g_submitting = true
        }
    }
}
function browser_version() {
    var A = navigator.userAgent.toLowerCase();
    return A.match(/msie ([\d.]+)/) ? 1 : A.match(/firefox\/([\d.]+)/) ? 3 : A.match(/chrome\/([\d.]+)/) ? 5 : A.match(/opera.([\d.]+)/) ? 9 : A.match(/version\/([\d.]+).*safari/) ? 7 : 1
}
function ptui_reportSpeed(D, C) {
    if (Math.random() > 0.1) {
        return
    }
    var A = browser_version();
    if (!global.flag2) {
        return
    }
    url = "http://isdspeed.qq.com/cgi-bin/r.cgi?flag1=6000&flag2=" + global.flag2 + "&flag3=" + A;
    for (var B = 0; B < g_speedArray.length; B++) {
        url += "&" + g_speedArray[B][0] + "=" + (g_speedArray[B][1] - D)
    }
    imgSendTimePoint = new Image();
    imgSendTimePoint.src = url
}
function ptui_VCReport() {
    if (Math.random() > 0.1) {
        return
    }
    if (g_imgTime < 5) {
        return
    }
    var A = browser_version();
    if (!global.flag2) {
        return
    }
    url = "http://isdspeed.qq.com/cgi-bin/r.cgi?flag1=6000&flag2=" + global.flag2 + "&flag3=" + A;
    url += "&5=" + g_checkTime + "&6=" + g_imgTime;
    imgAttr = new Image();
    imgAttr.src = url
}
function ptui_imgPoint() {
    if (g_imgTime < 1000000000000) {
        return
    }
    g_imgTime = new Date() - g_imgTime;
    ptui_VCReport()
}
function ptui_reportAttr(A) {
    if (Math.random() > 0.1) {
        return
    }
    url = "http://ui.ptlogin2." + g_domain + "/cgi-bin/report?id=" + A;
    imgAttr = new Image();
    imgAttr.src = url
}
function ptui_reportNum(B) {
    if (Math.random() > 0.1) {
        return
    }
    url = "http://ui.ptlogin2." + g_domain + "/cgi-bin/report?id=1000&n=" + B;
    var A = new Image();
    A.src = url
}
function imgLoadReport() {
    if (changeimg) {
        return
    }
    var A = new Date();
    var B = {};
    if (firstuin != "" && g_changeNum <= 1) {
        g_time.time8 = A;
        if (g_time.time1 && g_time.time3 && !xuiFrame && firstuin != "") {
            B["9"] = g_time.time8 - g_time.time1;
            B["10"] = g_time.time8 - g_time.time3;
            B["11"] = g_time.time8 - g_time.time7
        }
    } else {
        g_time.time11 = A;
        B["14"] = g_time.time11 - g_time.time10
    }
    ptui_speedReport(B)
}
function webLoginReport() {
    var A = {};
    if (g_time.time3 && g_time.time1) {
        A["7"] = g_time.time3 - g_time.time1
    }
    if (!xuiFrame && g_time.time1 && g_time.time3) {
        A["8"] = g_time.time4 - g_time.time1;
        A["22"] = js_bgnrun_time - g_time.time3;
        A["23"] = g_time.time4 - js_bgnrun_time
    }
    if (g_time.time2 && g_time.time2 > 0) {
        A["18"] = g_time.time1 - g_time.time2;
        A["21"] = g_time.time3 - g_time.time2;
        if (A["18"] > 60000 || A["21"] > 60000) {
            return
        }
    }
    if (g_time.time0 && g_time.time0 > 0) {
        A["19"] = g_time.time2 - g_time.time0;
        A["20"] = g_time.time3 - g_time.time0;
        if (A["19"] > 60000 || A["20"] > 60000) {
            return
        }
    }
    ptui_speedReport(A)
}
function ptui_speedReport(E) {
    if (!first) {
        return
    }
    if (!global.flag2) {
        return
    }
    var B = "http://isdspeed.qq.com/cgi-bin/r.cgi?flag1=6000&flag2=" + global.flag2 + "&flag3=" + browser_version();
    var C = 0;
    for (var D in E) {
        B += "&" + D + "=" + E[D];
        C++
    }
    if (C == 0) {
        return
    }
    var A = new Image();
    A.src = B
}
function ptui_checkValidate() {
    g_time.time12 = new Date();
    if (f_u.value == "") {
        alert("您还没有输入帐号！");
        f_u.focus();
        return false
    }
    f_u.value = ptui_trim(f_u.value);
    if (!ptui_checkQQUin(f_u.value)) {
        alert("请输入正确的帐号！");
        f_u.focus();
        f_u.select();
        return false
    }
    if (f_p.value == "") {
        alert("您还没有输入密码！");
        f_p.focus();
        return false
    }
    if (f_v.value == "") {
        if (!isLoadVC) {
            loadVC(true);
            g_submitting = true;
            return false
        }
        alert("您还没有输入验证码！");
        f_v.focus();
        if (!g_loadcheck) {
            ptui_reportAttr(78028)
        } else {
            ptui_reportAttr(78029)
        }
        return false
    }
    if (f_v.value.length < 4) {
        alert("请输入完整的验证码！");
        f_v.focus();
        f_v.select();
        return false
    }
    f_p.setAttribute("maxlength", "32");
    ajax_Submit();
    ptui_reportNum(g_changeNum);
    g_changeNum = 0;
    return false
}
var hexcase = 1;
var b64pad = "";
var chrsz = 8;
var mode = 32;
function md5_3(B) {
    var A = new Array;
    A = core_md5(str2binl(B), B.length * chrsz);
    A = core_md5(A, 16 * chrsz);
    A = core_md5(A, 16 * chrsz);
    return binl2hex(A)
}
function md5(A) {
    return hex_md5(A)
}
function hex_md5(A) {
    return binl2hex(core_md5(str2binl(A), A.length * chrsz))
}
function str_md5(A) {
    return binl2str(core_md5(str2binl(A), A.length * chrsz))
}
function core_md5(K, F) {
    K[F >> 5] |= 128 << ((F) % 32);
    K[(((F + 64) >>> 9) << 4) + 14] = F;
    var J = 1732584193;
    var I = -271733879;
    var H = -1732584194;
    var G = 271733878;
    for (var C = 0; C < K.length; C += 16) {
        var E = J;
        var D = I;
        var B = H;
        var A = G;
        J = md5_ff(J, I, H, G, K[C + 0], 7, -680876936);
        G = md5_ff(G, J, I, H, K[C + 1], 12, -389564586);
        H = md5_ff(H, G, J, I, K[C + 2], 17, 606105819);
        I = md5_ff(I, H, G, J, K[C + 3], 22, -1044525330);
        J = md5_ff(J, I, H, G, K[C + 4], 7, -176418897);
        G = md5_ff(G, J, I, H, K[C + 5], 12, 1200080426);
        H = md5_ff(H, G, J, I, K[C + 6], 17, -1473231341);
        I = md5_ff(I, H, G, J, K[C + 7], 22, -45705983);
        J = md5_ff(J, I, H, G, K[C + 8], 7, 1770035416);
        G = md5_ff(G, J, I, H, K[C + 9], 12, -1958414417);
        H = md5_ff(H, G, J, I, K[C + 10], 17, -42063);
        I = md5_ff(I, H, G, J, K[C + 11], 22, -1990404162);
        J = md5_ff(J, I, H, G, K[C + 12], 7, 1804603682);
        G = md5_ff(G, J, I, H, K[C + 13], 12, -40341101);
        H = md5_ff(H, G, J, I, K[C + 14], 17, -1502002290);
        I = md5_ff(I, H, G, J, K[C + 15], 22, 1236535329);
        J = md5_gg(J, I, H, G, K[C + 1], 5, -165796510);
        G = md5_gg(G, J, I, H, K[C + 6], 9, -1069501632);
        H = md5_gg(H, G, J, I, K[C + 11], 14, 643717713);
        I = md5_gg(I, H, G, J, K[C + 0], 20, -373897302);
        J = md5_gg(J, I, H, G, K[C + 5], 5, -701558691);
        G = md5_gg(G, J, I, H, K[C + 10], 9, 38016083);
        H = md5_gg(H, G, J, I, K[C + 15], 14, -660478335);
        I = md5_gg(I, H, G, J, K[C + 4], 20, -405537848);
        J = md5_gg(J, I, H, G, K[C + 9], 5, 568446438);
        G = md5_gg(G, J, I, H, K[C + 14], 9, -1019803690);
        H = md5_gg(H, G, J, I, K[C + 3], 14, -187363961);
        I = md5_gg(I, H, G, J, K[C + 8], 20, 1163531501);
        J = md5_gg(J, I, H, G, K[C + 13], 5, -1444681467);
        G = md5_gg(G, J, I, H, K[C + 2], 9, -51403784);
        H = md5_gg(H, G, J, I, K[C + 7], 14, 1735328473);
        I = md5_gg(I, H, G, J, K[C + 12], 20, -1926607734);
        J = md5_hh(J, I, H, G, K[C + 5], 4, -378558);
        G = md5_hh(G, J, I, H, K[C + 8], 11, -2022574463);
        H = md5_hh(H, G, J, I, K[C + 11], 16, 1839030562);
        I = md5_hh(I, H, G, J, K[C + 14], 23, -35309556);
        J = md5_hh(J, I, H, G, K[C + 1], 4, -1530992060);
        G = md5_hh(G, J, I, H, K[C + 4], 11, 1272893353);
        H = md5_hh(H, G, J, I, K[C + 7], 16, -155497632);
        I = md5_hh(I, H, G, J, K[C + 10], 23, -1094730640);
        J = md5_hh(J, I, H, G, K[C + 13], 4, 681279174);
        G = md5_hh(G, J, I, H, K[C + 0], 11, -358537222);
        H = md5_hh(H, G, J, I, K[C + 3], 16, -722521979);
        I = md5_hh(I, H, G, J, K[C + 6], 23, 76029189);
        J = md5_hh(J, I, H, G, K[C + 9], 4, -640364487);
        G = md5_hh(G, J, I, H, K[C + 12], 11, -421815835);
        H = md5_hh(H, G, J, I, K[C + 15], 16, 530742520);
        I = md5_hh(I, H, G, J, K[C + 2], 23, -995338651);
        J = md5_ii(J, I, H, G, K[C + 0], 6, -198630844);
        G = md5_ii(G, J, I, H, K[C + 7], 10, 1126891415);
        H = md5_ii(H, G, J, I, K[C + 14], 15, -1416354905);
        I = md5_ii(I, H, G, J, K[C + 5], 21, -57434055);
        J = md5_ii(J, I, H, G, K[C + 12], 6, 1700485571);
        G = md5_ii(G, J, I, H, K[C + 3], 10, -1894986606);
        H = md5_ii(H, G, J, I, K[C + 10], 15, -1051523);
        I = md5_ii(I, H, G, J, K[C + 1], 21, -2054922799);
        J = md5_ii(J, I, H, G, K[C + 8], 6, 1873313359);
        G = md5_ii(G, J, I, H, K[C + 15], 10, -30611744);
        H = md5_ii(H, G, J, I, K[C + 6], 15, -1560198380);
        I = md5_ii(I, H, G, J, K[C + 13], 21, 1309151649);
        J = md5_ii(J, I, H, G, K[C + 4], 6, -145523070);
        G = md5_ii(G, J, I, H, K[C + 11], 10, -1120210379);
        H = md5_ii(H, G, J, I, K[C + 2], 15, 718787259);
        I = md5_ii(I, H, G, J, K[C + 9], 21, -343485551);
        J = safe_add(J, E);
        I = safe_add(I, D);
        H = safe_add(H, B);
        G = safe_add(G, A)
    }
    if (mode == 16) {
        return Array(I, H)
    } else {
        return Array(J, I, H, G)
    }
}
function md5_cmn(F, C, B, A, E, D) {
    return safe_add(bit_rol(safe_add(safe_add(C, F), safe_add(A, D)), E), B)
}
function md5_ff(C, B, G, F, A, E, D) {
    return md5_cmn((B & G) | ((~B) & F), C, B, A, E, D)
}
function md5_gg(C, B, G, F, A, E, D) {
    return md5_cmn((B & F) | (G & (~F)), C, B, A, E, D)
}
function md5_hh(C, B, G, F, A, E, D) {
    return md5_cmn(B ^ G ^ F, C, B, A, E, D)
}
function md5_ii(C, B, G, F, A, E, D) {
    return md5_cmn(G ^ (B | (~F)), C, B, A, E, D)
}
function safe_add(A, D) {
    var C = (A & 65535) + (D & 65535);
    var B = (A >> 16) + (D >> 16) + (C >> 16);
    return (B << 16) | (C & 65535)
}
function bit_rol(A, B) {
    return (A << B) | (A >>> (32 - B))
}
function str2binl(D) {
    var C = Array();
    var A = (1 << chrsz) - 1;
    for (var B = 0; B < D.length * chrsz; B += chrsz) {
        C[B >> 5] |= (D.charCodeAt(B / chrsz) & A) << (B % 32)
    }
    return C
}
function binl2str(C) {
    var D = "";
    var A = (1 << chrsz) - 1;
    for (var B = 0; B < C.length * 32; B += chrsz) {
        D += String.fromCharCode((C[B >> 5] >>> (B % 32)) & A)
    }
    return D
}
function binl2hex(C) {
    var B = hexcase ? "0123456789ABCDEF": "0123456789abcdef";
    var D = "";
    for (var A = 0; A < C.length * 4; A++) {
        D += B.charAt((C[A >> 2] >> ((A % 4) * 8 + 4)) & 15) + B.charAt((C[A >> 2] >> ((A % 4) * 8)) & 15)
    }
    return D
}
isAbleSubmit = true;
function check() {
    var B = new Date();
    if (firstuin != "" && g_changeNum == 0) {
        g_time.time6 = B
    } else {
        g_time.time9 = B
    }
    var A = ptui_trim(f_u.value);
    if (g_uin == A || (!ptui_checkQQUin(A))) {
        return
    }
    g_changeNum++;
    g_uin = ptui_trim(f_u.value);
    ptui_needVC(g_uin, input_aid)
}
function loadVC(A) {
    if (isLoadVC == A && (lastUin == g_uin)) {
        return
    }
    lastUin = g_uin;
    isLoadVC = A;
    if (A == true) {
        var B = $("imgVerify");
        var E = g_uin;
        if (isNaN(g_uin) && (g_uin.indexOf("@") < 0)) {
            E = "@" + g_uin
        }
        var D = "/getimage?aid=" + input_aid + "&r=" + Math.random() + "&uin=" + E + "&vc_type=" + vc_type;
        if (g_https) {
            D = "." + D
        } else {
            D = "http://captcha." + g_domain + D
        }
        g_imgTime = new Date() - 0;
        B.src = D;
        $("verifyinput").style.display = "";
        $("verifytip").style.display = "";
        $("verifyshow").style.display = "";
        ptui_notifySize("login");
        try {
            f_p.focus()
        } catch(C) {}
    } else {
        $("verifyinput").style.display = "none";
        $("verifytip").style.display = "none";
        $("verifyshow").style.display = "none";
        ptui_notifySize("login")
    }
}
function onClickForgetPwd() {
    var A = $("label_forget_pwd");
    A.href = "http://ptlogin2.qq.com/ptui_forgetpwd";
    if (f_u != null) {
        if (A.href.indexOf("?") == -1) {
            A.href += "?"
        } else {
            A.href += "&"
        }
        A.href += "aquin=" + f_u.value
    }
    return true
}
onPrePageLoad();
/*  |xGv00|f443ba4d913d596bd3e47cffea446067 */
