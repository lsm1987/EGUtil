# Twitter
* Android
  * twitter-kit-android 3.1.1
    * 3.2.0 부터는 Java 8 필요하지만 아래 UE 코드에 의해 불가
    * Engine\Source\Programs\UnrealBuildTool\Android\UEDeployAndroid.cs
    * string AntOptions = AntBuildType + " -Djava.source=1.7 -Djava.target=1.7";
