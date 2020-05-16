function $(id){
  return document.getElementById(id);
}

function inputName(){
  var name=prompt("请输入您的名字：");
  if(name!=null)/*null只能小写*/
  {
    alert("您的名字是"+name);
    $("name1").value=name;
  }
  else {alert("请输入您的名字!");}
}

