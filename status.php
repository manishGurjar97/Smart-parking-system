<?php
// Fetch the response from the ESP32
$response = file_get_contents('http://192.168.43.239/status');

// Output the result directly
echo trim($response);
?>
