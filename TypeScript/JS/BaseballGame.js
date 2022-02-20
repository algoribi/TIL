const readline = require("readline");
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

let chkNumber = [false, false, false, false, false, false, false, false, false, false];
let ansNumber = [], counterTime = 1, zeroArr = [0, 0, 0];
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

    setAnswerNumber();
    console.log("답 : " + ansNumber); //
    /*
    while (ansFlag == 0)
        userInput();
    */
    userInput();
    gameReSet();
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

function userInput() {
    let userNumArr = [];

    console.log("> 숫자를 입력해 주세요 : ");
    rl.on("line", (line) => {
        userNumArr = line.split(' ').map(el => parseInt(el));
        rl.close();
    });
    rl.on('close', () => {
        chkAnswer(userNumArr);
        process.exit();
    })
    /*
    if (ansFlag == 0)
        userInput();
    */
}

function chkAnswer(arr) {
    let s = 0, b = 0;
    for (let i = 0; i < 3; i++) {
        if (arr[i] == ansNumber[i]) {
            s++;
        } else if (chkNumber[arr[i]] == true) {
            b++;
        }
    }
    
    // output
    if (JSON.stringify(arr) === JSON.stringify(zeroArr)) { // 사용자가 게임을 포기한 경우
        console.log("😵😵😵Give UP!!!😵😵😵");
        console.log("정답 : " + ansNumber);
        ansFlag = 2;
    } else if (counterTime == 1 && s == 3) { // 1회차 만에 맞혔을 경우
        console.log("💥⚾💥⚾홈~~~~~~~런💥⚾💥⚾");
        console.log("🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️");
        ansFlag = 1;
    } else if (counterTime > 1 && s == 3) { // 정답을 맞혔을 경우
        console.log(`✔ ${counterTime}회차 도전에 정답을 맞히셨습니다!`);
        console.log("🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️🙆‍♀️🙆‍♂️");
        ansFlag = 1;
    } else if (s == 0 && b == 0) { // 아웃일 경우
        console.log(`✔ ${counterTime}회차 도전 결과 : OUT!!`)
    } else {
        console.log(`✔ ${counterTime}회차 도전 결과 : ${s}S ${b}B`);
    }
}

function gameReSet() {
    console.log("⚾ 새로운 게임을 진행하시겠습니까?");
    console.log("- Yes는 1을, No는 아무 값을 입력해 주세요.");
    let n;
    rl.on("line", (line) => {
        n = line;
        n = parseInt(line);
        rl.close();
    });
    rl.on('close', () => {
        if (n == 1) {
            clearVar();
            console.log("-------새 게임을 시작합니다!-------");
            gameStart();
        } else {
            console.log("-------게임을 종료합니다!-------");
        }
        process.exit();
    })
}

function clearVar() {
    for (let i = 0; i < 10; i++) {
        if (chkNumber[i] == true)
            chkNumber[i] = false;
    }
    ansNumber.splice(0, 3);
    counterTime = 1;
    ansFlag = 0;
}
