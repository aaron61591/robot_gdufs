<!--
    Document   : index.html
    Created on : 2013-6-2, 14:27:23
    Author     : Aaron Peng
-->
<!DOCTYPE html>
<html>
    <head>
        <title>广外机器人</title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="./public/css/reset.css"/>
        <link rel="stylesheet" type="text/css" href="./public/css/index.css"/>
        <script type="text/javascript" src="./public/js/jquery.js"></script>
        <script type="text/javascript" src="./public/js/index.js"></script>
    </head>
    <body style="background-color: #FEFEFE;">
        <div id="welcome">
            <div id="wel_box" align="center">
                <p id="wel_font">欢迎使用广外机器人</p>
                <!--<p class="wel_font">英文模块</p>-->
                <p class="wel_font" style="font-size: 15px; color: red;">（本应用目前只支持中文对话）</p>
                <p class="wel_font" id="wel_font2" >点击进入</p>
            </div>
        </div>
        <div id="background"></div>
        <div id="teach_field">
            <div id="teach_box">
                <div class="teach_content">
                    <p class="teach_font">当我和你说：</p>
                    <p align="center">
                        <input id="teach_input1" type="text" maxLength="25" />
                    </p>
                </div>
                <div class="teach_content">
                    <p class="teach_font">你记得要说：</p>
                    <p align="center">
                        <input id="teach_input2" type="text" maxLength="25" />
                    </p>
                </div>
                <div id="teach_emotion" align="center">
                    <img id="e2" class="emotion" width="55" height="55" src="./public/images/G-Robot2.jpg"/>
                    <img id="e3" class="emotion" width="45" height="45" src="./public/images/G-Robot3.jpg"/>
                    <img id="e4" class="emotion" width="45" height="45" src="./public/images/G-Robot4.jpg"/>
                    <img id="e5" class="emotion" width="45" height="45" src="./public/images/G-Robot5.jpg"/>
                    <img id="e6" class="emotion" width="45" height="45" src="./public/images/G-Robot6.jpg"/>
                </div>
                <div id="teach_ajax"></div>
                <div class="teach_content" align="center" style="margin-top: 0px;">
                    <img id="teach_button1" class="teach_button" src="./public/images/icon_submit.jpg" />
                    <img id="teach_button2" class="teach_button" src="./public/images/icon_cancel.jpg" />
                </div>
            </div>
        </div>
        <div id="discuss_field">
            <div id="discuss_box">
                <div class="discuss_content">
                    <p class="discuss_font2">游客名：</p>
                    <input id="name_input" name="guest_name" type="text" maxLength="10"/>
                </div>
                <div class="discuss_content">
                    <p class="discuss_font2">吐嘈：</p>
                    <textarea id="discuss_input" row="2" maxLength="25"></textarea>
                </div>
                <div id="discuss_ajax"></div>
                <div class="discuss_content">
                    <img id="discuss_submit" class="discuss_button" src="./public/images/icon_submit.jpg" />
                    <img id="discuss_cancel" class="discuss_button" src="./public/images/icon_cancel.jpg" />
                </div>
            </div>
        </div>
        <div id="header">
            <div id="logo"><font id="logo_font"><font style="color:#FFEF94;">广外</font>-机器人</font></div>
            <div id="column">
                <font id="home" class="column_font">首页</font>
                <font id="discuss_region" class="column_font">吐槽区</font>
                <font id="about_us" class="column_font">关于我们</font>
            </div>
        </div>
        <div class="menu" id="main">
            <div id="left_bar">
                <div class="box">
                    <div class="img_box" align="center" valign="center">
                        <div style="height: 2px;"></div>
                        <img id="head_img1" width="98%" height="170" src="./public/images/guest.jpeg" />
                    </div>
                    <div class="introduce" align="center">
                        <!--<p class="name">Welcome to use</p>-->
                        <p class="detail">就随便和他说几句吧~</p>
                        <p class="detail">但是记得说中文啊~</p>
                    </div>
                    <hr class="split"/>
                    <div align="center">
                        <textarea id="input_field" maxlength="20" rows="2" ></textarea>
                    </div>
                    <div align="center">
                        <img id="img_button1" class="img_button" src="./public/images/icon_send.jpg" />
                    </div>
                </div>
            </div>
            <div id="left_box" onmouseover="left_box();">
                <div class="box" id="left_ajax">
                </div>
            </div>
            <div id="right_box">
                <div class="box" id="right_ajax">
                </div>
            </div>
            <div id="right_bar">
                <div class="box">
                    <div class="img_box" align="center" valign="center">
                        <div style="height: 2px;"></div>
                        <img id="head_img2" width="98%" height="170" src="./public/images/G-Robot1.jpg" />
                    </div>
                    <div class="introduce" align="center">
                        <p class="name">广外机器人</p>
                        <p class="detail">不要嫌我笨啊，我说得不好你教我呗~</p>
                    </div>
                    <hr class="split"/>
                    <div align="center">
                        <img id="img_button2" class="img_button" src="./public/images/icon_teach.jpg" />
                    </div>
                </div>
            </div>
            <div style="clear: both;"></div>
        </div>
        <div class="menu" id="about_us_div">
            <div id="about">
                <div class="box2">
                    <p id="about_head">关于我们</p>
                    <hr class="split"/>
                    <p class="about_font2">工作组成员:</p>
                    <p class="about_font">贾超峰：Java工程师、洗衣殴、伟大的NoLogo人民领袖</p>
                    <p class="about_font">彭海洋：Linux c/c++、PHP工程师</p>
                    <p class="about_font">贺子诚：Java工程师、Dota资深战术研究员</p>
                    <p class="about_font">钟逸维：CCIE网络工程师</p>
                    <p class="about_font2">联系我们:</p>
                    <p class="about_font">手机：15989107035/617035</p>
                    <p class="about_font">Mail：<a href="mailto: aaron61591@gmail.com">aaron61591@gmail.com</a></p>
                    <p class="about_font">QQ：529523494</p>
                    <p class="about_font2">版权声明:</p>
                    <p class="about_font">本应用除校徽表情和头像来源于网络，其他均为原创，如有问题，请与我们联系，谢谢</p>
                </div>
            </div>
        </div>
        <div class="menu" id="discuss">
            <div id="talk">
                <div class="box2">
                    <p id="about_head">吐嘈区</p>
                    <hr class="split"/>
                    <input type="hidden" name="discuss_count" value="0"/>
                    <div id="discuss_main">
                        <?php
                        $con = mysql_connect("localhost", "root", "root");
                        if (!$con) {
                            die('Could not connect: ' . mysql_error());
                        }
                        mysql_select_db("g-robot", $con);
                        $result = mysql_query("SELECT * FROM discuss ORDER BY time DESC LIMIT 6;");
                        while ($row = mysql_fetch_array($result)) {
                            echo "<div class=\"discuss_box\">
                            <p class=\"guest_name\">".$row['author']."&nbsp;&nbsp;<font class=\"time\">".date('M j,y H:i',$row['time'])."</font></p>
                            <p class=\"discuss_font\">".$row['message']."</p>
                        </div>";
                        }
                        mysql_close($con)
                        ?>
                    </div>
                    <div align="center">
                        <img id="discuss_button" src="./public/images/icon_discuss.jpg" />
                    </div>
                </div>
            </div>
        </div>
        <div align="center" style="position: relative; top: 100px;">
            <hr class="split2"/>
            <font id="foot_bar">© 2013 NoLogo Studio</font>
        </div>
    </body>
</html>
