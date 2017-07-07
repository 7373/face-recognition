<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>
<body>
<center>
<h1>注册界面</h1>
<form action="RegisterAction.action" id="form" method="post">
<ul>
<li> 姓　　名：<input type=text name=temp.name id=name></li>
<li> 身份证号：<input type=text name=temp.code id=id></li>
</ul>
<br><input type=submit value="提交"><br><br>

</form>

</center>
</body>
</html>