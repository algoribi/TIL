# 6장 객체와 자료 구조

> clean code 6장 리뷰

변수를 private로 선언하더라도 각 값마다 get/set 함수를 제공한다면 구현을 외부로 노출하는 셈이다. (p.119)

</br>

## 자료 추상화

인터페이스나 조회/설정 함수만으로 구현이 저절로 감춰지는 것은 아니다. 아래의 코드를 보자.

```java
// 코드 1 : 구체적인 Vehicle 클래스
// 두 함수가 변수값을 읽어 반환할 뿐이라는 사실이 거의 확실하다.
public interface Vehicle {
	double getFuelThankCapacityInGallons();
	double getGallonsOfGasoline();
}
```

```java
// 코드 2 : 추상적인 Vehicle 클래스 (구현을 완전히 숨김)
// 연료 상태를 백분율이라는 추상적인 개념으로 알려줘 정보가 어디서 오는지 알 수 없게 했다.
public interface Vehicle {
	double getPercentFuelRemaining();
}
```

이렇듯 자료는 세세하게 공개하기 보다는 추상적인 개념으로 표현하는 편이 좋다. </br>
이렇듯 개발자는 객체가 포함하는 자료를 표현할 가장 좋은 방법을 심각하게 고민해야 한다.

</br>

## 자료/객체 비대칭

> 객체와 자료 구조는 본질적으로 상반된다. 두 개념은 사실상 정반대다. (p.120)

- 객체는 자료를 숨긴 채 자료를 다루는 함수만 공개한다.
- 자료 구조는 자료를 그대로 공개하며 별다른 함수는 제공하지 않는다.

```java
public class Suare {
	public Point topLeft;
	public double side;
}

public class Restangle {
	public Point topLeft;
	public double height;
	public double width;
}

public class Circle {
	public Point center;
	public double radius;
}

public class Geometry {
	PI = 3.141592653589793;

	public double area(Object shape) throws NoSuchShapeException {
		if (shape instanceof Square) {
			Square s = (Square)shape;
			return s.side * s.side;
		} else if (shape instanceof Rectangle) {
			Rectangle r = (Rectangle)shape;
			return r.height * r.width;
		} else if (shape instanceof Circle) {
			Circle c = (Circle)shape;
			return PI * c.radius * c.radius;
		}
		throw new NoSuchShapeException();
	}
}
```

위의 코드는 자료 구조를 사용하는 **절차적**인 도형 클래스이다. Geometry 클래스는 세 가지 도형 클래스를 다룬다. 각 도형 클래스는 아무 메서드도 제공하지 않는 간단한 자료 구조로 되어있다. 도형이 동작하는 방식은 Geometry 클래스에서 구현한다.

여기서 만약 둘레 길이를 구하는 perimeter() 함수를 추가해야 한다고 가정해보자. 이때 도형 클래스들은 아무런 영향도 받지 않는다.
반대로 새 도형을 추가하고 싶다면? Geometry 클래스에 속한 함수를 모두 고쳐야 한다.

이처럼 자료 구조를 사용하는 절차적인 코드는 기존 자료 구조를 변경하지 않으면서 새 함수를 추가하기 쉽고, 새로운 자료 구조는 추가하기 어렵다. 그러려면 모든 함수를 고쳐야 한다.

```java
public class Square implements Shape {
	private Point topLeft;
	private double side;

	public double area() {
		return side * side;
	}
}

public class Retangle implements Shape {
	private Point topLeft;
	private double height;
	private double width;

	public double area() {
		return hieght * width;
	}
}

public class Circle implements Shape {
	private Point center;
	private double radius;
	private final double PI = 3.141592653589793;

	public double area() {
		return PI * radius * radius;
	}
}
```

위의 코드는 **객체 지향적**인 도형 클래스다. 여기서 area()는 다형 메서드로 부모의 메서드를 오버라이딩한 것이기 때문에 만약 새 도형을 추가해도 기존 함수에 아무런 영향을 미치지 않는다.
반대로 둘레 길이를 구하는 perimeter() 함수를 새로 추가하고 싶다면? 도형 클래스를 전부 고쳐야 한다.

> 다시 말해, 객체 지향 코드에서 어려운 변경은 절차적인 코드에서 쉬우며, 절차적인 코드에서 어려운 변경은 객체 지향 코드에서 쉽다! (p. 122)

결국 객체와 자료구조는 상호 보완적인 특징을 가지고 있으며, 좋은 프로그래머는 상황에 따라 객체 지향적인 코드나 절차적인 코드를 적절하게 선택할 줄 알아야 한다.

- **Q.** 단순한 코드 질문. area()는 인터페이스를 통해 오버라이드 하는 메서드인데, 예제 코드에서는 어째서 함수 앞에 @override 어노테이션을 붙이지 않는 것인지? (다른 이유가 있는지?)

- **Q.**

</br>

## 디미터 법칙

> 모듈은 자신이 조작하는 객체의 속사정을 몰라야 한다. (p.123)

객체 지향 프로그래밍에서 가장 중요한 것은 "객체가 어떤 데이터를 가지고 있는가?"가 아니라, **"객체가 어떤 메시지를 주고받는가?"** 이다.

디미터 법칙의 핵심은 객체 구조의 경로를 따라 멀리 떨어져 있는 낯선 객체에 접근하는 설계는 피하라는 것이다. 이는 **객체 간 결합도를 낮추기 위해서**이다. 따라서 디미터 법칙이 위배된다는 것은 올바른 객체 지향 프로그래밍을 하지 못하고 있다는 증거이기도 하다.

예제 코드를 통해 디미터의 법칙을 이해해보자. 우리는 서울에 살고 있는 어떤 사용자에게 알림을 보내주는 함수를 구현한다고 하자.

```java
@Getter
public class User {
	private String email;
	private String name;
	private Address address;
}

@Getter
public class Address {
	private String region;
	private String details;
}

public class NotificationService {
	public void sendMessageForSeoulUser(final User user) {
		if("서울".equals(user.getAddress().getRegion())) { // 기차 충돌
			sendNotification(user);
		}
	}
}
```

위 코드의 경우 디미터의 법칙을 위반하고 있는 코드이며 객체지향스럽지 못하다. 왜냐하면 우리는 객체에게 메시지를 보내는 것이 아니라 객체가 가지는 자료를 확인하고 있으며, 다른 객체가 어떤 자료를 갖고 있는지 지나치게 잘 알기 때문이다.

> 객체라면 **뭔가를 하라고** 말해야지 속을 드러내라고 말하면 안 된다. (p.125)

getAddress() 함수가 반환하는 객체의 getRegion() 함수를 호출한 후 그 함수가 반환하는 객체를 통해 값을 검사하기 때문이다. 흔히 이런 코드를 **기차 충돌**이라고 부른다.

이를 디미터의 법칙을 준수하는 코드로 고쳐본다.

```java
public class Address {
	private String region;
	private String details;

	public boolean isSeoulRegion() {
		return "서울".equals(region);
	}
}

public class User {
	private String email;
	private String name;
	private Address address;

	public boolean isSeoulUser() {
		return address.isSeoulRegion();
	}
}

public class NotificationService {
	public void sendMessageForSeoulUser(final User user) {
		if(user.isSeoulUser()) {
			sendNotification(user);
		}
	}
}
```

수정된 코드를 보면 NotificationService 함수에서 User객체와 Address 객체가 어떠한 데이터들을 지니고 있는지 모른 채 작업을 수행할 수 있다. 즉, 내부 구조를 잘 감추게 된 것이다.

</br>

## 자료 전달 객체

> 자료 구조체의 전형적인 형태는 공개 변수만 있고 함수가 없는 클래스다. 이런 자료 구조체를 때로는 자료 전달 객체(DTO)라 한다. (p.126)
