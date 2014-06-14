Option Explicit

Dim objFileSys
Dim strScriptPath
Dim strReadFile
Dim strWriteFile
Dim objReadStream
Dim objWriteStream
Dim strText

Set objFileSys = CreateObject("Scripting.FileSystemObject")

strScriptPath = Replace(WScript.ScriptFullName,WScript.ScriptName,"")
strReadFile = objFileSys.BuildPath(strScriptPath,"TestData.txt")
strWriteFile = objFileSys.BuildPath(strScriptPath,"WriteData.txt")

Set objReadStream = objFileSys.OpenTextFile(strReadFile, 1)
Set objWriteStream = objFileSys.OpenTextFile(strWriteFile, 2, True)

Do Until objReadStream.AtEndOfLine = True

   strText = objReadStream.ReadLine

   If Mid(strText, 28, 1) = "M" Then
      objWriteStream.WriteLine strText
      WScript.echo strText
   End If

Loop

objReadStream.Close
objWriteStream.Close

Set objReadStream = Nothing
Set objWriteStream = Nothing
Set objFileSys = Nothing