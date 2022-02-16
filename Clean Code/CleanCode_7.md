# 7장 오류 처리

> 깨끗한 코드와 오류 처리는 확실히 연관성이 있다. 상당수 코드 기반은 전적으로 오류 처리 코드에 좌우된다. (p.130)

## 오류 코드보다 예외를 사용하라
> 이전까지만 해도 예외를 지원하지 않는 프로그래밍 언어가 많았다. (p.130)

예외를 지원하지 않는 언어는 오류를 처리하고 보고하는 방법이 제한적이었다. 오류 플래그를 설정하거나 호출자에게 오류 코드를 반환하는 방법이 전부였다. 

```java
public class DeviceController {

	...

	DeviceHandle handle = getHandle(DEV1);
	if (handle != DeviceHandle.INVALID) {
		retrieveDeviceRecord(handle);
		if (record.getStatus() != DEVICE_SUSPENDED) {
			closeDevice(handle);
		} else {
			logger.log("Device suspended. Unable to shut down");
		}
	} else {
		logger.log("Invalid handle");
	}

	...
}
```
기존의 오류 코드는 함수를 호출한 즉시 오류를 확인해야 하기 때문에 호출자 코드가 복잡해진다. 이는 논리와 오류가 뒤섞인 형태로 보기에 좋지 않다. 

위의 코드를 오류 발견 시 예외를 던지는 코드로 고쳐본다.

```java
public class DeviceController {

	...

	public void sendShutDown() {
		try {
			tryToShutDown();
		}
		catch (DeviceShutDownError e) {
			logger.log(e);
		}
	}

	private void tryToShutDown() {
		DeviceHandle handle = getHandle(DEV1);
		DeviceRecord record = retrieveDeviceRecord(handle);

		pauseDevice(handle);
		clearDeviceWorkQueue(handle);
		closeDevice(handle);
	}

	private DeviceHandle getHandle(DeviceId id) {
		...
		throw new DeviceShutDownError("Invalid handle for: " + id.toString());
		...
	}
	
	...

}
```

보기 좋아졌을 뿐 아니라, 코드 품질도 나아졌다. 앞서 뒤섞였던 개념, 즉 디바이스를 종료하는 알고리즘과 오류를 처리하는 알고리즘을 분리했기 때문이다. 

</br>

## Try-Catch-Finally 문부터 작성하라

try문에서 무슨 일이 생기든 catch 블록은 프로그램 상태를 일관성 있게 유지한다. 따라서 예외가 발생할 코드를 짤 대는 try-catch문으로 시작하는 편이 낫다. 

```java
try { 
	// 예외가 발생할 가능성이 있는 문장 
	} catch(Exception1 e1) { 
		...
	} catch(Exception2 e2) { 
		...
	} catch(ExceptionN eN) { 
		...
	} finally { 
		// 예외 발생 여부에 관계없이 상항 수행되어야 하는 문장을 적는다.
		// 보통은 자원이나 DB에 커넥션 한 경우, 파일 닫기, 연결 닫기(close) 등과 같은 "정리"코드를 넣는 데 사용된다.
	}
```

1. 강제로 예외를 일으키는 테스트 케이스를 작성한 후 테스트를 통과하게 코드를 작성한다.
2. TDD(테스트 주도 개발)에서는 try-catch 구조로 범위를 정의하고, 필요한 나머지 논리를 추가한다.

이렇게 되면 try 블록의 트랜잭션(DB의 상태를 변화시키기 위해 수행하는 작업의 단위) 범위부터 구현하게 되므로 트랜잭션 본질을 유지하기 쉬워진다.

</br>

## 미확인(unchecked) 예외를 사용하라
> 확인된 예외는 선언부의 수정을 필요로 하기 때문에 모듈의 캡슐화를 깨버리기 때문이다. (p.134)

최상위 함수가 아래 함수를 호출한다. 아래 함수는 그 아래 함수를 호출한다. 단계를 내려갈수록 호출하는 함수 수는 늘어난다.

만약 최하위 함수가 **확인된 오류**를 던진다면 함수는 선언부에 throws 절을 추가해야 한다. 그러면 해당 함수를 호출하는 모든 함수가 </br>
1. catch 블록에서 새로운 예외를 처리하거나 </br>
2. 선언부에 throws 절을 추가해야 한다.

즉, 하위 단계에서 코드를 변경하면 최상위 단계까지 연쇄적인 수정이 일어난다는 뜻이다.

이는 모듈과 관련된 코드가 전혀 바뀌지 않았더라도 (선언부가 바뀌었으므로) 모듈을 다시 빌드한 다음 배포해야 한다는 말이다.

따라서 지금은 안정적인 소프트웨어를 제작하는 요소로 확인된 예외가 반드시 필요하지는 않다는 사실이 분명해졌다.

</br>

## 예외에 의미를 제공하라
> 예외를 던질 때는 전후 상황을 충분히 덧붙인다. 실패한 코드의 의도를 파악하려면 호출 스택만으로 부족하다. (p.135)

- 오류 메시지에 정보(실패한 연산 이름, 실패 유형 등)를 담아 예외와 함께 던진다.

</br>

## 호출자를 고려해 예외 클래스를 정의하라
> 오류를 정의해 분류하는 방법은 프로그래머에게 오류를 잡아내는 방법이 되어야 한다.

아래 코드의 경우 오류를 형편없이 분류한 사례다. 

```java
ACMEPort port = new ACMEPort(12); // 외부 라이브러리

try {
	port.open();
} catch (DeviceResponseException e) {
	reportPortError(e);
} catch (ATM1212UnlockedException e) {
	reportPortError(e);
} catch (GMXError e) {
	reportPortError(e);
} finally {
	...
}
```

이 코드는 외부 라이브러리가 던질 예외를 모두 잡아낸다. 이런 구조는 외부 라이브러리와 프로그램 사이의 의존성이 높아진다. 

이걸 감싸기(Wrapper) 클래스를 통해 호출하는 라이브러리 API를 감싸는 구조로 변경해 보겠다.

```java
LocalPort port = new LocalPort(12);
try {
	port.open();
} catch (PortDeviceFailure e) {
	reportError(e);
	logger.log(e.getMessage(), e);
} finally {
	...
}
```
```java
public class LocalPort { // Wrapper 클래스
	private ACMEPort innerPort; // 외부 라이브러리
	
	public LocalPort(int portNumber) {
		innerPort = new ACMEPort(portNumber);
	}
	
	public void open() {
		try{
			innerPort.open();
		} catch (DeviceResponseException e) {
			throw new PortDeviceFailure(e);
		} catch (ATM1212UnlockedException e) {
			throw new PortDeviceFailure(e);
		} catch (GMXError e) {
			throw new PortDeviceFailure(e);\
		}
	}
	...
}
```

이런 감싸기(Wrapper) 클래스로 API를 감싸면 좋은 점은 다음과 같다.
1. 외부 API를 감싸면 외부 라이브러리와 프로그램 사이에 의존성이 크게 줄어든다. 따라서 나중에 다른 라이브러리로 갈아타도 비용이 적다.
2. 특정 업체가 API를 설계한 방식에 발목 잡히지 않는다. 프로그램이 사용하기 편한 API를 정의하면 그만이다.

</br>

## 정상 흐름을 정의하라
> 대개는 멋진 처리 방식이지만, 때로는 중단이 적합하지 않은 때도 있다. (p.137)

**특수 사례 패턴**으로 클래스를 만들거나 객체를 조작해 특수 사례를 처리하면 클라이언트 코드가 예외적인 상황을 처리할 필요가 없어진다.

```java
try {
	MealExpenses expenses = expenseReportDAO.getMeals(employee.getID());
	m_total += expenses.getTotal();
} catch(MealExpensesNotFound e) {
	m_total += getMealPerDiem();
}
```

위의 코드는 식비를 비용으로 청구했다면 식비를 총계에 더하는 것이고 청구하지 않았다면 기본 식비를 반환하는 코드이다. 그런데 예외가 논리를 따라가기 어렵게 만든다. 코드를 더 간단하게 만들 수는 없을까?

```java
	MealExpenses expenses = expenseReportDAO.getMeals(employee.getID());
	m_total += expenses.getTotal();
```
```java
public class PerDiemMealExpenses implements MealExpenses {
	public int getTotal() {
		// 기본값으로 일일 기본 식비를 반환한다.
	}
}
```
ExpenseReportDAO를 고쳐 언제나 MealExpense 객체를 반환하게 한다. 즉, 청구한 식비가 없다면 일일 기본 식비를 반환하는 MealExpense 객체를 반환하면 된다.

즉, 이 예제에서 처럼 클래스를 만들거나 객체를 조작해 예외 처리를 없앨 수 있는 특수 사례의 경우 정상 흐름대로 정의하는 것이 좋다는 뜻이다.

</br>

## null을 반환하지 마라
> 우리가 흔히 저지르는 바람에 오류를 유발하는 행위 중 하나가 null을 반환하는 습관이다. (p.139)

null을 반환하고 이를 **if(object != null)** 의 형태로 확인하는 방식은 나쁘다.
- 메서드를 짤 때 null을 반환하는 대신 예외를 던지거나 특수 사례 객체를 반환해라.
- 사용하려는 외부 API가 null을 반환한다면 Wrapper를 구현해 예외를 던지거나 특수 사례 객체를 반환해라.

```java
List<Employee> employees = getEmployees();
if (employees != null) {
	for(Employee e : employees) {
		totalPay += e.getPay();
	}
}
```

위의 코드에서 getEmployees()는 null도 반환한다. 하지만 반드시 null을 반환할 필요가 있을까? </br>
getEmployees()가 null 대신 빈 리스트를 반환하도록 수정하도록 해보자.

```java
List<Employee> employees = getEmployees();
for(Employee e : employees) {
	totalPay += e.getPay();
}
```

이렇게 코드를 변경하면 코드도 깔끔해질뿐더러 NullPointerException이 발생할 가능성도 줄어든다.

더 나아가 자바에는 Collections.emptyList()가 있어 미리 정의된 읽기 전용 리스트를 반환할 수도 있다. 

```java
public List<Employee> getEmployees() {
	if ( ...직원이 없다면... ) {
		return Collections.emptyList();
	}
}
```

어쨌든, null을 반환하는 것은 지양하도록 하자.

</br>

## null을 전달하지 마라
> 메서드에서 null을 반환하는 방식도 나브지만 메서드로 null을 전달하는 방식은 더 나쁘다. (p.140)

정상적인 인수로 null을 기대하는 API가 아니라면 메서드로 null을 전달하는 코드는 최대한 지양한다.

대다수 프로그래밍 언어는 호출자가 실수로 넘기는 null을 적절히 처리하는 방법이 없다. 그렇다면 애초에 null을 넘기지 못하도록 금지하는 정책이 합리적이다. 