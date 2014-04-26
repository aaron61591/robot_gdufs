<?php

$con = mysql_connect("localhost", "root", "root");
if (!$con) {
    die('Could not connect: ' . mysql_error());
}

mysql_select_db("g-robot", $con);

switch ($_POST['action']) {
    case 'add':
        if ($_POST['name'] == "")
            $name = $_SERVER['REMOTE_ADDR'];
        else
            $name = strip_tags($_POST['name']);
        $sql = "INSERT INTO discuss (author, message, ip, time) VALUES ('" . $name . "','" . addslashes(strip_tags($_POST['content'])) . "','" . $_SERVER['REMOTE_ADDR'] . "'," . time() . ")";
        if (!mysql_query($sql, $con)) {
            die('Error: ' . mysql_error());
        }
        break;
    case 'check':
        $sql = "SELECT COUNT(*) FROM discuss";
        $result = mysql_query($sql);
        $row = mysql_fetch_array($result);
        $page_size = 6;
        $page_num = ceil($row[0] / $page_size);
        $start = ($_POST['now'] + 1) >= $page_num ? 0 : ($_POST['now'] + 1) * $page_size;
        $result = mysql_query("SELECT * FROM discuss ORDER BY time DESC LIMIT " . $start . ",6;");
        $data['content'] = "";
        while ($row = mysql_fetch_array($result)) {
            $data['content'].= "<div class=\"discuss_box\">
                            <p class=\"guest_name\">" . $row['author'] . "&nbsp;&nbsp;<font class=\"time\">" . date('M j,y H:i', $row['time']) . "</font></p>
                            <p class=\"discuss_font\">" . $row['message'] . "</p>
                        </div>";
        }
        $data['count'] = ($_POST['now'] + 1) >= $page_num ? 0 : ($_POST['now'] + 1);
        echo json_encode($data, JSON_UNESCAPED_UNICODE);
        break;
}

mysql_close($con)
?>