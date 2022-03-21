# material-dashboard-react-clone-coding study

## html

- %PUBLIC_URL% : npm run build를 실행하면 CreateReact App이 %Public_URL%을 절대 경로로 대체하므로 클라이언트 측 라우팅을 사용하거나 루트가 아닌 URL에서 호스트를 해도 프로젝트가 작동한다. [source](https://think0wise.tistory.com/21)

- noscript 태그 : 페이지의 스크립트 유형을 지원하지 않거나, 브라우저가 스크립트를 비활성화한 경우 보여줄 HTML 구획을 정의한다. 

### meta 태그

- name="viewport" : 모바일을 포함하여 모든 장치에서 웹 사이트가 잘 보이도록 뷰포트를 설정하는 속성값이다. [source](https://aboooks.tistory.com/352)

- name="theme-color" : 모바일 환경에서 브라우저의 툴바(toolbar)영역의 색상을 바꿀 수 있다. [source](https://www.hahwul.com/2020/01/24/how-to-set-toolbar-color-on-mobile-chrome/)

### link 태그
> link 태그는 해당 문서와 외부 소스(external resource) 사이의 관계를 정의할 때 사용한다. <link> 요소는 빈 태그로 속성만을 포함하며, <head> 요소 내부에만 위치할 수 있다. [source](http://www.tcpschool.com/html-tags/link)

- rel="shortcut icon" : 숏컷 아이콘은 브라우저 탭에서 타이틀 옆에 있는 이미지 아이콘이다. 이를 파비콘(favicon.ico)이라고 한다. [source](https://webdir.tistory.com/337)

- rel="apple-touch-icon" : iOS 2.0 이상과 Android 2.1 이상에서는 터치(Touch) 아이콘 지정이 가능하다. 고해상(152*152)의 파비콘 하나만 준비하면 저해상도에서는 알아서 아이콘의 크기가 변경된다. 

- rel="manifest" : 웹 앱 매니페스트(Web app manifest)는 프로그레시브 웹 앱(PWA)라고 칭하는 웹 기술 모음집의 일부로서, 앱 스토어를 거치지 않고 장치의 홈 화면에 설치할 수 있는 웹사이트를 구성한다. PWA는 사전 다운로드를 통해 오프라인에서도 동작하며 일반적인 Web API도 사용할 수 있다. 웹 앱 매니페스트는 웹 애플리케이션의 정보를 JSON 텍스트 파일로 제공하여, 웹 앱의 다운로드 및 네이티브 앱과 유사한 형태로 제공을 가능케 한다. [source](https://developer.mozilla.org/ko/docs/Web/Manifest)

- rel="stylesheet" : 외부 스타일 시트(external style sheet)와의 연결시 사용한다.

- integrity 옵션 : <link> 태그나 <script> 태그에서 이용 가능하다. 만약 integrity 옵션의 설정값(해시값)과 다르다면 로드되지 않는다.(로드를 차단) 이를 통해 특정 버전의 파일이 변경되거나 변조된 경우를 막아 악의적인 스크립트 변조를 막을 수 있다. [source](https://hi098123.tistory.com/273)

- crossorigin 옵션 : 리소스를 가져올 때 CORS를 사용해야 하는지 나타내는 옵션이다. [source](https://developer.mozilla.org/ko/docs/Web/HTML/Element/link)




