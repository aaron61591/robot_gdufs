<?php

error_reporting(E_ALL);
set_time_limit(0);
if (strlen($_POST['message']) == 0) {
    die(">o<  don't...treat me...like that...");
}
$message_send['act'] = $_POST['action'];
$message_send['ip'] = $_SERVER['REMOTE_ADDR'];
$message_send['info'] = format_message(strip_tags($_POST['message']));
if($message_send['info']==""){
    $message="1你在说什么？？？";
    echo get_result($message);
    die();
}
$message_send['info2'] = format_message(strip_tags($_POST['message2']));
$message_send['info3'] = $_POST['emotion'];
$message_send = json_encode($message_send, JSON_UNESCAPED_UNICODE);
//echo 'Sended: ' . $message_send . '<br/>';
//die();
$address = '127.0.0.1';
$port = 5000;
$length = 1024;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
    die();
}
$result = socket_connect($socket, $address, $port);
if ($result === false) {
//    echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
    echo get_result("3服务器正在维护中，请稍候。。。");
    die();
}
if (socket_write($socket, $message_send, strlen($message_send)) === false) {
    echo "socket_write() failed reason:" . socket_strerror(socket_last_error($socket)) . "\n";
}
$message_tmp = "test";
while ($message_tmp) {
    $message_tmp = socket_read($socket, $length);
    $message.=$message_tmp;
}
echo get_result($message);
socket_close($socket);

function format_message($message) {

    $tmp = '';
    for ($i = 0; $i < strlen($message); ++$i) {
        switch ($message[$i]) {
            case '"':
                break;
            case '/';
                break;
            case ' ';
                break;
            default :
                $tmp.=$message[$i];
        }
    }
    return $tmp;
}

function get_result($message) {

    $result['emotion'] = $message[0];
    $result['message'] = substr($message, 1);
    $message=json_encode($result,JSON_UNESCAPED_UNICODE);
    return $message;
}

?>