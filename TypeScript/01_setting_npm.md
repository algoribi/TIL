# npm(Node Package Manager) 소개와 설치

## npm이란?

Node Package Manager의 약자이다. 이름처럼 npm은 Node.js의 패키지를 설치하고 관리해주는 도구이다.

```
ex) Python의 pip, Ruby의 gem 등...
```

일반적인 경우 npm은 Node.js를 설치하면 자동으로 설치된다.

## 설치

> [Node.js 설치 페이지](https://nodejs.org/en/)

설치 페이지를 보면 LTS와 Stable 버전이 있는데 차이는 다음과 같다.

- LTS(Long Term Supported) 버전 : 짝수 버전이 LTS 버전으로 안정성과 보안성에 초점을 두어 개발한다.
- Stable 버전 : 홀수 버전이 Stable 버전으로 잦은 업데이트를 진행한다.

프론트 개발은 Stable 버전을 서버로 사용하려면 LTS를 추천한다.

## VSCode package.json Setting

먼저 VSCode에서 Workspace로 활용할 프로젝트 디렉토리를 생성한다. 나는 Nodejs로 만들어줬다.

이제 VSCode에서 생성한 Node.js 프로젝트 디렉토리를 열어준다.

터미널창에서 `npm init` 명령어를 실행한다.

```
PS D:\...\workSpace\Nodejs> npm init
This utility will walk you through creating a package.json file.
It only covers the most common items, and tries to guess sensible defaults.

See `npm help init` for definitive documentation on these fields
and exactly what they do.

Use `npm install <pkg>` afterwards to install a package and
save it as a dependency in the package.json file.

Press ^C at any time to quit.
package name: (nodejs)
version: (1.0.0)
description:
entry point: (index.js)
test command:
git repository:
keywords:
author:
license: (ISC)
About to write to D:\reed\workSpace\Nodejs\package.json:

{
  "name": "nodejs",
  "version": "1.0.0",
  "description": "",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC"
}


Is this OK? (yes)
npm notice
npm notice New minor version of npm available! 8.4.1 -> 8.5.1
npm notice Changelog: https://github.com/npm/cli/releases/tag/v8.5.1
npm notice Run npm install -g npm@8.5.1 to update!
npm notice

PS D:\...\workSpace\Nodejs>
```

`npm init`는 node.js를 실행하기 위한 initial 과정으로 이 과정을 통해 package.json 파일을 프로젝트 디렉토리에 생성해준다.

package.json은 npm을 통해 생성되는 node관련 component들의 dependency를 관리하는 모듈로서, Maven의 pom.xml과 비슷한 역할이라 생각하면 이해가 쉬울 수 있다.

다음으로 `npm install`을 실행한다.

```
PS D:\...\workSpace\Nodejs> npm install

added 50 packages, and audited 51 packages in 2s

2 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities
```

npm install를 통해 package-lock.json과 node_modules라는 디렉토리가 생성되었다.

package.json 파일을 보면 하단에 dependencies가 생성된 것을 볼 수 있는데, 이는 Node.js을 Runtime으로 실행할 경우 실제 Application Package와 함께 packaging 되는 Library 파일로 자동으로 버전 관리가 이루어질 수 있도록 한다.

또한 devDependencies로 추가되는 경우 배포하기 위한 패키징에 포함시키지 않도록 구분하여 관리할 수 있다. 쉽게 생각하자면 Testing 관련 라이브러리, 로그 관련 라이브러리 등 개발 환경에서 분석을 위해 추가한 라이브러리를 운영환경에 적용하지 않도록 관리할 수 있는 라이브러리 디펜던시라 할 수 있다.

<img src="img/01.png" width="300px"></img><br/>

설치를 무사히 마쳤다면 위와 같이 탐색기에서

1. npm init으로 생성한 package.json
2. npm install로 생성한 node_module
   을 확인할 수 있다.

</br>

## package.json

> 노드로 확장 모듈을 작성하면 npm을 통해 중앙 저장소로 배포할 수 있다. package.json 파일은 배포한 모듈 정보를 담고자 만들어졌지만, 노드로 작성하는 애플리케이션도 package.json 파일을 사용하여 관리할 수 있다. 이는 확장 모듈 형태로 배포하기 위한 것이 아니더라도 애플리케이션을 개발할 때 package.json 파일을 이용하면 사용하는 확장 모듈에 대한 의존성 관리가 가능하여 편리하기 때문이다.

package.json는 직접 작성할 수도 있고 `npm init` 명령을 통해서 자동으로 생성할 수도 있습니다. 그리고 해당 애플리케이션을 위해 사용한 확장 모듈에 대한 정보는 `npm install -save`를 통해 자동으로 모듈에 대한 정보를 추가할 수 있다.

package.json는 기본적으로 **프로젝트에 대한 명세**라고 할 수 있다.

```json
{
  "name": "test",
  "description": "javascript's test programming.",
  "keywords": ["util", "f", "server", "client", "browser"],
  "author": "Goorm",
  "contributors": [],
  "dependencies": [],
  "repository": {
    "type": "git",
    "url": "git://gitbub.com/documentcloud/test.git"
  },
  "main": "test.js",
  "version": "1.1.6"
}
```

- name : 프로젝트의 이름으로 가장 중요하다. 중앙 저장소에 배포할 때 version과 함께 필수 항목이다. 이는 url로 사용되고, 설치할 때 디렉토리 이름이 되기 때문에 url이나 디렉터리에서 쓸 수 없는 이름을 사용하면 안 된다. 또한, 이름에 node나 js가 들어가면 안 된다. name은 214자보다 짧아야 하며, 점(.)이나 밑줄(\_)로 시작할 수 없습니다. 대문자를 포함해서는 안 되며, require() 함수의 인수로 사용되며 짧고 알기 쉬운 것으로 짓는 것이 좋다.

- version : 프로젝트 버전을 정의한다. 3단계 버전을 사용하며, -로 태그 이름을 적을 수 있다.

- description : 프로젝트 설명으로, 문자열로 기술한다. npm search로 검색된 리스트에 표시되기 때문에 사람들이 패키지를 찾아내고 이해하는 데 도움이 된다.

- author : 프로젝트 작성자 정보로, 한 사람만을 지정한다. JSON 형식으로 name, email, url 옵션을 포함한다.

- contributors : 프로젝트에 참여한 공헌자 정보로, 여러 사람을 배열로 지정할 수 있다.

- repository : 프로젝트의 소스 코드를 저장한 저장소의 정보이다. 소스 코드에 참여하고자 하는 사람들에게 도움이 될 수 있다. 프로젝트의 홈페이지 url을 명시해서는 안 된다.

- scripts : 프로젝트에서 자주 실행해야 하는 명령어를 scripts로 작성해두면 npm 명령어로 실행 가능하다.

- dependencies : 프로젝트의 의존성 관리를 위한 부분이다. 이 프로젝트가 어떤 확장 모듈을 요구하는지 정리할 수 있다. 일반적으로 package.json에서 가장 많은 정보가 입력되는 곳이다. 애플리케이션을 설치할 때 이 내용을 참조하여 필요한 확장 모듈을 자동으로 설치한다. 따라서 개발한 애플리케이션이 특정한 확장 모둘을 사용한다면 여기에 꼭 명시를 해줘야 한다. 또한, npm install 명령은 여기에 포함된 모든 확장 모듈들을 설치하게 되어 있다.

- devDependencies : 개발할 때만 의존하는 확장 모듈을 관리한다.

- keywords : 프로젝트를 검색할 때 참조되는 키워드이다. description과 마찬가지로 npm search로 검색된 리스트에 표시된다.

- homepage : 프로젝트 홈페이지 주소이다. url 항목과는 다르며, url을 설정하면 예상치 못한 움직임을 하게 되므로 주의한다.

- config : 소스 코드에서 config 필드에 있는 값을 환경 변수처럼 사용할 수 있다.

- private : 이 값을 true로 작성하면 중앙 저장소로 저장하지 않는다.

- engine : 실행 가능한 노드 버전의 범위를 결정한다.

[참고](https://programmingsummaries.tistory.com/385)

</br>

## VSCode에서 node.js 실행해보기

test.js 파일을 만들어 다음과 같은 코드를 작성하고, 터미널 창에서 무사히 실행되는지 확인해본다.

```node.js
var num1 = 10;
var num2 = 20;
var num3 = num1 + num2;

console.log(num3);
```

`node .\[file name].js`

<img src="img/02.png" width="300px"></img><br/>

## TypeScript

`npm install --save-dev ts-node`

`npm install --save-dev typescript`

`npm run ts-start`
