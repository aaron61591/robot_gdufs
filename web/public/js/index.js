//    Document   : index.html
//  Created on : 2013-6-2, 14:27:23
//  Author     : Aaron Peng

$(document).ready(function() {

    //welcome animate
    var wel = true;
    $("#wel_font2").click(function() {
        if (wel) {
            $(".wel_font").animate({opacity: 0});
            setTimeout("$(\"#wel_font\").animate({marginTop: \"20%\"},\"slow\")", 600);
            setTimeout("$(\"#wel_font\").animate({fontSize: \"50px\",opacity: 0,marginTop: \"15%\"},\"slow\")", 1500);
            setTimeout("$(\"#welcome\").animate({opacity: 0},\"slow\")", 1500);
            setTimeout("$(\"#background\").animate({opacity: 0},\"slow\")", 1500);
            setTimeout("$(\"#background\").css(\"display\", \"none\")", 2500);
            setTimeout("$(\"#welcome\").css(\"display\", \"none\")", 2500);
            $("#input_field").focus();
            auto_chat();
            wel = false;
        }
    });

    //auto chat module
    recent_chat = false;
    if_reply = true;
    if_teaching = false;

    //button change
    $("#img_button1,#img_button2,#teach_button1,#teach_button2,#discuss_button,#discuss_submit,#discuss_cancel").mouseover(function() {
        var new_image;
        switch ($(this).attr("id")) {
            case 'img_button1':
                new_image = "./public/images/icon_send2.jpg";
                break;
            case 'img_button2':
                new_image = "./public/images/icon_teach2.jpg";
                break;
            case 'teach_button1':
                new_image = "./public/images/icon_submit2.jpg";
                break;
            case 'teach_button2':
                new_image = "./public/images/icon_cancel2.jpg";
                break;
            case 'discuss_button':
                new_image = "./public/images/icon_discuss2.jpg";
                break;
            case 'discuss_submit':
                new_image = "./public/images/icon_submit2.jpg";
                break;
            case 'discuss_cancel':
                new_image = "./public/images/icon_cancel2.jpg";
                break;
        }
        $(this).attr("src", new_image);
    });
    $("#img_button1,#img_button2,teach_button1,teach_button2,#discuss_button,#discuss_submit,#discuss_cancel").mouseout(function() {
        var new_image;
        switch ($(this).attr("id")) {
            case 'img_button1':
                new_image = "./public/images/icon_send.jpg";
                break;
            case 'img_button2':
                new_image = "./public/images/icon_teach.jpg";
                break;
            case 'teach_button1':
                new_image = "./public/images/icon_submit.jpg";
                break;
            case 'teach_button2':
                new_image = "./public/images/icon_cancel.jpg";
                break;
            case 'discuss_button':
                new_image = "./public/images/icon_discuss.jpg";
                break;
            case 'discuss_submit':
                new_image = "./public/images/icon_submit.jpg";
                break;
            case 'discuss_cancel':
                new_image = "./public/images/icon_cancel.jpg";
                break;
        }
        $(this).attr("src", new_image);
    });

    //head_img change
    $("#head_img1").mouseover(function() {
        setTimeout("$(\"#head_img1\").stop().animate({opacity: 0.85})", 100);
    });
    $("#head_img1").mouseout(function() {
        setTimeout("$(\"#head_img1\").stop().animate({opacity: 1})", 100);
    });
    $("#head_img2").mouseover(function() {
        var img = "./public/images/G-Robot" + Math.round(Math.random() * 6) + ".jpg";
        $("#head_img2").css("opacity", "0.2");
        $("#head_img2").attr("src", img);
        setTimeout("$(\"#head_img2\").stop().animate({opacity: 1},\"slow\")", 0);
    });
    $("#head_img2").mouseout(function() {
        $("#head_img2").css("opacity", "1");
    });

    //div change
    var start_chat = false;
    $("#left_box,#right_box").mouseover(function() {
        if (start_chat)
            $(this).stop().animate({opacity: 0.7});
    });
    $("#left_box,#right_box").mouseout(function() {
        if (start_chat)
            $(this).stop().animate({opacity: 1});
    });

    //input field
    $("#input_field,#teach_input1,#teach_input2,#name_input,#discuss_input").focus(function() {
        $(this).css("border-color", "rgb(50, 50, 255) rgb(100, 100, 255) rgb(100, 100, 255) rgb(100, 100, 255)");
    });
    $("#input_field,#teach_input1,#teach_input2,#name_input,#discuss_input").blur(function() {
        $(this).css("border-color", "rgb(180, 180, 180) rgb(200, 200, 200) rgb(200, 200, 200) rgb(200, 200, 200)");
    });

    //button function
    var if_teach = false;
    $("#img_button2").click(function() {
        if_teach = true;
        key_mod = "teach";
        if_teaching = true;
        $("#background").css("display", "block");
        $("#teach_field").css("display", "block");
        $("#background").animate({opacity: 1});
        $("#teach_field").animate({opacity: 1});
        $("#teach_ajax").html("");
        $("#teach_input1").val("");
        $("#teach_input2").val("");
        $("#teach_input1").focus();
    });
    $("#teach_button2").click(close_teach);
    $("#img_button1").click(function() {
        var message = $("#input_field").val();
        $("#input_field").focus();
        if (message !== "") {
            if_reply = true;
            recent_chat = true;
            $("#input_field").val("");
            start_chat = true;
            $("#left_box").animate({opacity: 1});
            $("#right_box").animate({opacity: 1});
            var box1 = $(".msg_box1");
            if (box1.length < 3) {
                var new_data = "<div class=\"msg_box1\"><div class=\"msg_img_left\" align=\"center\"><img width=\"75%\" height=\"45\" src=\"./public/images/guest.jpeg\" /></div><div class=\"msg_content_left\"><div class=\"msg_content1\">Brin <font class=\"time\">" + get_time() + "</font></div><div class=\"msg_content2\">" + message + "</div></div></div>";
                if (box1.length !== 2) {
                    new_data += "<hr class=\"split3\"/>";
                }
                $("#left_ajax").html($("#left_ajax").html() + new_data);
            } else {
                var new_data = "<div class=\"msg_box1\">" + $(".msg_box1:eq(1)").html() + "</div><hr class=\"split3\"/>";
                new_data += "<div class=\"msg_box1\">" + $(".msg_box1:eq(2)").html() + "</div><hr class=\"split3\"/>";
                new_data += "<div class=\"msg_box1\"><div class=\"msg_img_left\" align=\"center\"><img width=\"75%\" height=\"45\" src=\"./public/images/guest.jpeg\" /></div><div class=\"msg_content_left\"><div class=\"msg_content1\">Brin <font class=\"time\">" + get_time() + "</font></div><div class=\"msg_content2\">" + message + "</div></div></div>";
                $("#left_ajax").html(new_data);
            }
            $("#left_ajax").css({opacity: 0.7});
            $("#left_ajax").stop().animate({opacity: 1}, 1000);
            $.post("./client.php",
                    {
                        action: "chat",
                        message: message,
                        message2: "",
                        emotion: ""
                    },
            function(data, status) {
                var result = eval("(" + data + ")");
                answer(result.emotion, result.message);
            });
        }
    });
    var emotion = "e2";
    $("#teach_button1").click(function() {
        if (if_teach) {
            var question = $("#teach_input1").val();
            var answer = $("#teach_input2").val();
            if (question !== "" && answer !== "") {
                $.post("./client.php",
                        {
                            action: "teach",
                            message: question,
                            message2: answer,
                            emotion: emotion[1]
                        },
                function() {

                    $("#teach_ajax").html("<img src=\"./public/images/correct.jpg\">&nbsp;&nbsp;好的，我记住了！");
                    setTimeout("close_teach()", 1500);
                }
                );
            }
            if_teach = false;
        }
    });
    $(".emotion").click(function() {
        emotion = $(this).attr("id");
        $(".emotion").attr("width", "45");
        $(".emotion").attr("height", "45");
        $(this).attr("width", "55");
        $(this).attr("height", "55");
    });

    $("#discuss_main").click(function() {
        $.post("./server.php",
                {
                    action: 'check',
                    now: $("input[name='discuss_count']").val()
                },
        function(data) {
            var result = eval("(" + data + ")");
            $("input[name='discuss_count']").val(result.count);
            $("#discuss_main").css("opacity", "0");
            $("#discuss_main").html(result.content);
            setTimeout("$(\"#discuss_main\").animate({opacity: 1})", 200);
        }
        );
    });
    $("#discuss_button").click(function() {
        key_mod = "discuss";
        $("#background").css("display", "block");
        $("#discuss_field").css("display", "block");
        $("#background").animate({opacity: 1});
        $("#discuss_field").animate({opacity: 1});
        $("#discuss_ajax").html("");
        $("#name_input").val("");
        $("#discuss_input").val("");
        $("#name_input").focus();
    });
    var if_discuss = false;
    $("#discuss_submit").click(function() {
        var name = $("#name_input").val();
        var content = $("#discuss_input").val();
        if (content !== "") {
            if (!if_discuss) {
                if_discuss = true;
                $.post("./server.php",
                        {
                            action: 'add',
                            name: name,
                            content: content
                        },
                function(data) {

                    $("#discuss_ajax").html("<img src=\"./public/images/correct.jpg\">&nbsp;&nbsp;吐嘈成功！");
                    setTimeout("$(\"#discuss_cancel\").click()", 1500);
                    $.post("./server.php",
                            {
                                action: 'check',
                                now: -1
                            },
                    function(data) {
                        var result = eval("(" + data + ")");
                        $("input[name='discuss_count']").val(result.count);
                        $("#discuss_main").css("opacity", "0");
                        $("#discuss_main").html(result.content);
                        setTimeout("$(\"#discuss_main\").animate({opacity: 1})", 200);
                    }
                    );
                }
                );
            }
        }
    });
    $("#discuss_cancel").click(function() {
        if_discuss = false;
        key_mod = "chat";
        $("#input_field").focus();
        $("#background").animate({opacity: 0});
        $("#discuss_field").animate({opacity: 0});
        setTimeout("$(\"#background\").css(\"display\", \"none\")", 1000);
        setTimeout("$(\"#discuss_field\").css(\"display\", \"none\")", 1000);
    });

    //column button
    $("#logo_font,#home,#about_us,#discuss_region").click(function() {
        var menu_class = $(this).attr("id");
        var div_id = '';
        switch (menu_class) {
            case 'logo_font':
                div_id = '#main';
                break;
            case 'home':
                div_id = '#main';
                break;
            case 'about_us':
                div_id = '#about_us_div';
                break;
            case 'discuss_region':
                div_id = '#discuss';
                break;
        }
        $(".menu").stop().animate().animate({opacity: 0}, 1000);
        setTimeout("$(\".menu\").stop().css(\"display\",\"none\")", 1000);
        setTimeout("$(\"" + div_id + "\").stop().css(\"display\",\"block\")", 1000);
        setTimeout("$(\"" + div_id + "\").stop().animate({opacity: 1}, 1000)", 1000);
        if (div_id === '#main') {
            setTimeout("$(\"#input_field\").focus()", 1000);
        }
    });

    $(document).keydown(function(event) {
        switch (event.keyCode) {
            case 13:
                switch (key_mod) {
                    case 'chat':
                        $("#img_button1").click();
                        event.preventDefault();
                        break;
                    case 'teach':
                        $("#teach_button1").click();
                        event.preventDefault();
                        break;
                    case 'discuss':
                        $("#discuss_submit").click();
                        event.preventDefault();
                        break;
                }
                break;
            case 27:
                switch (key_mod) {
                    case 'chat':
                        $("#wel_font2").click();
                        break;
                    case 'teach':
                        close_teach();
                        break;
                    case 'discuss':
                        $("#discuss_cancel").click();
                        break;
                }
                break;
        }
    });

});

//keyboard event
var key_mod = "chat";
function get_time() {

    var time = new Date();
    var y = (time.getYear() < 1900) ? (1900 + time.getYear()) : time.getYear();
    y -= 2000;
    var m = time.getMonth() + 1;
    var d = time.getDate();
    var h = time.getHours();
    var i = time.getMinutes();
    return h + ':' + i + ' ' + m + ' ' + d + ',' + y;
}

function close_teach() {

    key_mod = "chat";
    if_teaching = false;
    $("#input_field").focus();
    $("#background").animate({opacity: 0});
    $("#teach_field").animate({opacity: 0});
    setTimeout("$(\"#background\").css(\"display\", \"none\")", 1000);
    setTimeout("$(\"#teach_field\").css(\"display\", \"none\")", 1000);
}

var chat_data = new Array();
for (var i = 0; i < 5; ++i) {
    chat_data[i] = new Array();
}
chat_data[0][0] = "1";
chat_data[0][1] = "你怎么不跟我讲话啦？";
chat_data[1][0] = "5";
chat_data[1][1] = "好无聊啊。。。";
chat_data[2][0] = "0";
chat_data[2][1] = "世界上总有一半人不理解另一半人的快乐";
chat_data[3][0] = "3";
chat_data[3][1] = "大师兄，你知道吗？二师兄的肉现在比师傅的都贵了";
chat_data[4][0] = "2";
chat_data[4][1] = "人不能在一棵树上吊死，要在附近几棵树上多死几次试试";
chat_data[5][0] = "0";
chat_data[5][1] = "有些人，有些事，看清了，也就看轻了。";

function auto_chat() {

    var index = [Math.round(Math.random() * (chat_data.length - 1))];
    setTimeout("$(\"#right_box\").animate({opacity: 1});if (if_reply&&!recent_chat&&!if_teaching) {answer(\"" + chat_data[index][0] + "\",\"" + chat_data[index][1] + "\");if_reply=false;} else {recent_chat = false;}auto_chat();", 10000);
}

function answer(emotion, data) {
    var box2 = $(".msg_box2");
    var img = "./public/images/G-Robot" + emotion + ".jpg";
    if (box2.length < 3) {
        var new_data = "<div class=\"msg_box2\"><div class=\"msg_img_right\" align=\"center\"><img width=\"75%\" height=\"45\" src=\"" + img + "\" /></div><div class=\"msg_content_right\"><div class=\"msg_content1\">机器人<font class=\"time\">" + get_time() + "</font></div><div class=\"msg_content2\">" + data + "</div></div></div>";
        if (box2.length !== 2) {
            new_data += "<hr class=\"split3\"/>";
        }
        $("#right_ajax").html($("#right_ajax").html() + new_data);
    } else {
        var new_data = "<div class=\"msg_box2\">" + $(".msg_box2:eq(1)").html() + "</div><hr class=\"split3\"/>";
        new_data += "<div class=\"msg_box2\">" + $(".msg_box2:eq(2)").html() + "</div><hr class=\"split3\"/>";
        new_data += "<div class=\"msg_box2\"><div class=\"msg_img_right\" align=\"center\"><img width=\"75%\" height=\"45\" src=\"" + img + "\" /></div><div class=\"msg_content_right\"><div class=\"msg_content1\">机器人<font class=\"time\">" + get_time() + "</font></div><div class=\"msg_content2\">" + data + "</div></div></div>";
        $("#right_ajax").html(new_data);
    }
    $("#head_img2").css("opacity", "0.2");
    $("#head_img2").attr("src", img);
    setTimeout("$(\"#head_img2\").animate({opacity: 1},\"slow\")", 0);
    $("#right_ajax").css({opacity: 0.7});
    $("#right_ajax").stop().animate({opacity: 1}, 1000);
}