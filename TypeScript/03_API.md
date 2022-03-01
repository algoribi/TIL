## REST API 설계하기

> Representational State Transfer

클라이언트는 서버와 API라는 체계를 이용하여 **요청과 응답**을 주고받는다. 그리고 더 체계적으로 API를 관리하기 위해 나온 것이 REST API이다.

REST란

1. HTTP URI(Uniform Resource Identifier)를 통해 자원(Resource)을 명시하고,
2. HTTP Method(POST, GET, PUT, DELETE)를 통해
3. 해당 자원(URI)에 대한 CRUD Operation을 적용하는 것을 의미합니다.

즉, REST API란 REST의 설계 규칙을 따르는 API를 의미한다.

### HTTP Method와 CRUD

클라이언트가 서버에게 요청을 보낼 때 이 요청의 성격을 크게 'Create', 'Read', 'Update', 'Delete' 이 4가지로 분류할 수 있다. 이에 맞게 HTTP Method 또한 GET, POST, PUT, DELETE 가 있다.

- Read = GET : 서버에서 정보를 불러오는 요청이다. 이는 GET 메서드를 사용해 요청한다.

- Create, Update, Delete = POST : Read를 제외한 서버에 정보를 올리고, 바꾸고, 삭제하는 동작 모두는 POST 메서드를 통해 요청한다. 실질적으로 Update, Delete 작업 또한 POST를 통해 처리해도 문제없다.

### HTTP 상태 코드

클라이언트가 요청을 보내면 서버는 응답을 한다. 이때 응답은 성공일 수도, 실패일 수도 있다.

- 200 : 성공은 200번대 코드로 표현된다. (ex. 200, 201 ...)
- 400 : 클라이언트의 요청에 문제가 있는 경우, 400번대 코드로 표현된다. (ex. 401, 402, 404 ...)
- 500 : 서버에 문제가 있는 경우, 500번대의 코드로 표현된다. (ex. 500, 501 ...)

### JSON

웹 API를 만들 때 고려하는 요소 중 하나로 API에 전달할 '인자 데이터'와 '응답받는 데이터'의 **형식**일 것이다. JSON은 웹 API에서 보편화되고 가장 많이 이용되는 데이터 형식이다.

- {} : 객체를 담는다.
- [] : 배열을 담는다.

```JSON
{
    "회사": [
        {
           "이름": "Apple",
           "운영체제": [
               "macOS",
               "iOS"
                       ]
        },
        {
           "이름": "Microsoft",
           "운영체제": [
               "MS-DOS",
               "Windows"
                       ]
        }
    ]
}
```

### REST API 설계 규칙

- URI는 동사보다는 명사를, 대문자보다는 소문자를 사용한다.

```
Bad Example : http://algoribi.com/Running
Good Example : http://algoribi.com/run
```

- 마지막에 슬래시(/)를 포함하지 않는다.

```
Bad Example : http://algoribi.com/test/
Good Example : http://algoribi.com/test
```

- 언더바(\_) 대신 하이폰(-)을 사용한다.

```
Bad Example : http://algoribi.com/test_blog
Good Example : http://algoribi.com/test-blog
```

- 파일 확장자는 URI에 포함하지 않는다.

```
Bad Example : http://algoribi.com/photo.jpg
Good Example : http://algoribi.com/photo
```

- 행위를 포함하지 않는다.

```
Bad Example : http://algoribi.com/delete-post/1
Good Example : http://algoribi.com/post/1
```
