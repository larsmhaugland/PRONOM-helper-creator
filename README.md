# PRONOM-helper-creator

This c++ program creates a switch for matching PRONOM PUID strings to the full name with version. It is intended to be used in [FileConverter]([https://github.com/larsmhaugland/file-converter](https://github.com/larsmhaugland/file-converter/blob/main/src/HelperClasses/PronomHelper.cs)). It parses an CSV report from [National Archives](https://www.nationalarchives.gov.uk/PRONOM/Format/proFormatSearch.aspx?status=new), just search by file format without specifying an extension and save the report as CSV. 

## Usage:
```sh
MakePronomHelper.exe <Input file>                  # Writes to output.txt
MakePronomHelper.exe <Input file> <Output file>    # Writes to specified file
```

Example output:
```csharp
string output;
switch(pronom){
case ""        : output = Empty                                                       ; break;
case default   : output = Unknown                                                     ; break;
case "fmt/1"   : output = "Broadcast WAVE 0 Generic"                                  ; break;
case "fmt/2"   : output = "Broadcast WAVE 1 Generic"                                  ; break;
//(...)
case "x-fmt/455": output = "AutoCAD Drawing 2007-2008"                                ; break;
}
return output;
```

