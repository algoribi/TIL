const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let chkNumber = [false, false, false, false, false, false, false, false, false, false];
let ansNumber = [], counterTime = 1, zeroArr = [0, 0, 0], chkReGame = 0;
let ansFlag = 0; // 0 : 정답이 아닌 상태, 1 : 정답을 맞힌 상태, 2 : 사용자가 게임을 포기한 상태

infoPrint();
gameStart();

function infoPrint() {
    console.log("-------------⚾숫자 야구 게임⚾-------------");
    console.log("* 사용되는 숫자는 0 ~ 9의 서로 다른 숫자입니다.");
    console.log("* 숫자는 맞지만 위치가 틀렸을 때는 볼");
    console.log("* 숫자와 위치가 전부 맞으면 스트라이크");
    console.log("* 숫자와 위치가 전부 틀리면 아웃");
    console.log("* '0 0 0'을 입력 시에 포기하는 것으로 간주하고 답을 출력해 줍니다.");
    console.log("⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾⚾");
}

function gameStart() {
    let input = [];

    setAnswerNumber();

    console.log("> 숫자를 입력해 주세요.");
    rl.on('line', function (line) {
        input = line.split(' ').map((el) => parseInt(el));
        
        if (chkReGame == 0) {
            chkAnswer(input);

            input.splice(0);
            counterTime++;
            
            if (ansFlag != 0) {
                reGamePrint();
                chkReGame = 1;
            } else 
                console.log("> 숫자를 입력해 주세요.");
        } else {
            if (input[0] == 1) {
                gameReSet();
            } else {
                console.log("-------게임을 종료합니다!-------");
                rl.close();
            }
        }
    });
    rl.on('close', function () {
        process.exit();
    });
}

function setAnswerNumber() {
    let pickNum, counterNum = 0;
    while (counterNum < 3) {
        pickNum = Math.floor(Math.random() * 10);
        if (chkNumber[pickNum] == false) {
            chkNumber[pickNum] = true;
            ansNumber.push(pickNum);
            counterNum++;
        }
    }
}

function chkAnswer(arr) {
    let numberI = [false, false, false, false, false, false, false, false, false, false]; // 사용자의 룰 미숙지로 중복 값 입력 시, s혹은 b의 카운트의 중복을 막기 위해 체크
    let s = 0, b = 0;
    for (let i = 0; i < 3; i++) {
        if (numberI[arr[i]] == false && arr[i] == ansNumber[i])
            s++;
        else if (numberI[arr[i]] == false && chkNumber[arr[i]] == true)
            b++;
        numberI[arr[i]] = true;
    }
    
    // output
    if (JSON.stringify(arr) === JSON.stringify(zeroArr)) { // 사용자가 게임을 포기한 경우
        console.log("😵😵😵Give UP!!!😵😵😵");
        console.log("정답 : " + ansNumber + "\n");
        ansFlag = 2;
    } else if (counterTime == 1 && s == 3) { // 1회차 만에 맞혔을 경우
        console.log("💥⚾💥⚾홈~~~~~~~런💥⚾💥⚾");
        console.log("🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️\n");
        ansFlag = 1;
    } else if (counterTime > 1 && s == 3) { // 정답을 맞혔을 경우
        console.log(`✔ ${counterTime}회차 도전에 정답을 맞히셨습니다!`);
        console.log("🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️\n");
        ansFlag = 1;
    } else if (s == 0 && b == 0) { // 아웃일 경우
        console.log(`✔ ${counterTime}회차 도전 결과 : OUT!!\n`)
    } else {
        console.log(`✔ ${counterTime}회차 도전 결과 : ${s}S ${b}B\n`);
    }
}

function reGamePrint() {
    console.log("⚾⚾⚾ 게임 종료!!! ⚾⚾⚾");
    console.log("⚾ 새로운 게임을 진행하시겠습니까?");
    console.log("- Yes는 1을, No는 아무 값을 입력해 주세요.");
}

function gameReSet() {
    setAnswerNumber();

    for (let i = 0; i < 10; i++) {
        if (chkNumber[i] == true)
            chkNumber[i] = false;
    }
    ansNumber.splice(0, 3);
    counterTime = 1;
    ansFlag = 0;
    chkReGame = 0;
    
    console.log("-------새 게임을 시작합니다!-------");
    console.log("> 숫자를 입력해 주세요.");
}