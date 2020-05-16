function $(id) {
  return document.getElementById(id);
}
function checkcardno() {
  var no = $("cardno").value;
  $("err_cardno").innerHTML = " ";
  if (no == " " || no == null) {
    $("err_cardno").innerHTML = "卡号不能为空";
  }
  else if (no.length != 10) {
    $("err_cardno").innerHTML = "卡号长度必须10";
  }
  else {
    var prime = no.charAt(0);
    if (prime == '0') {
      $("err_cardno").innerHTML = "首字母不能为0";
    }
    else if (parseInt(no) < 1000000000) {
      $("err_cardno").innerHTML = "卡号不全为数字";
      alert("卡号不全为数字");
    }
  }
}

function checkkey() {
  var key = $("key").value;
  $("err_key").innerHTML = " ";
  if (key == " " || key == null) {
    $("err_key").innerHTML = "卡号不能为空";
  }
  else if (key.length > 15 || key.length < 8) {
    $("err_key").innerHTML = "口令长度在8到15之间";
  }
}

function checkkey1() {
  var key1 = $("key1").value;
  var key = $("key").value;
  $("err_key1").innerHTML = " ";

  if (key1 == " " || key1 == null) {
    $("err_key1").innerHTML = "卡号不能为空";
  }
  else if (key1.length > 15 || key1.length < 8) {
    $("err_key1").innerHTML = "口令长度在8到15之间";
  }
  else if (key != key1) {
    $("err_key1").innerHTML = "二次口令与口令不同";
  }
}

function checkqqwx() {
  var qqwx = $("qqwx").value;
  $("err_qqwx").innerHTML = " ";
  if (qqwx == " " || qqwx == null) {
    $("err_qqwx").innerHTML = "卡号不能为空";
  }
}

function check()//提交时验证
{
  var cardno = $("err_cardno").innerHTML;
  var key = $("err_key").innerHTML;
  var key1 = $("err_key1").innerHTML;
  var qqwx = $("err_qqwx").innerHTML;
  if (cardno == " " && key == " " && key1 == " " && qqwx == " ")//所有的都通过才能提交
    return true;
  else {
    alert("未规范输入，不能提交");
    return false;
  }
}