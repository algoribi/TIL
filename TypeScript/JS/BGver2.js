const readline = require('readline');
const { start } = require('repl');
const { isNumberObject } = require('util/types');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

class BaseballGame {
    constructor () {
        this.answerNumberArray = MakeAnswerNumber();
        //test code
        console.log(this.answerNumberArray);
        this.counterTime = 1;
        console.log("-------새 게임을 시작합니다!-------");
    }

    inputUserNumber() {
        const answerNumber = this.answerNumberArray;

        console.log("> 숫자를 입력해 주세요.");
        rl.on('line', function (line) {
            const userNumber = line.split(' ');
            
            if (line == 'give up') {
                console.log(`give up!!!\n정답 : ${answerNumber}\n`);
                process.exit();
            } else if (!CheckInputFormat(userNumber)) {
                InputGuidePrint();
            } else if (CompareUserNumberAndAnswerNumber(answerNumber, userNumber)) {
                process.exit();
            }

            this.counterTime++;
        });
    }

}

// TODO : test code
const BG = new BaseballGame();
BG.inputUserNumber(BG.answerNumberArray);

function GameTitlePrint() {
    console.log("----------------숫자 야구 게임----------------");
    console.log("* 사용되는 숫자는 0 ~ 9의 서로 다른 숫자입니다.");
    console.log("* 숫자는 맞지만 위치가 틀렸을 때는 볼");
    console.log("* 숫자와 위치가 전부 맞으면 스트라이크");
    console.log("* 숫자와 위치가 전부 틀리면 아웃");
}

function MakeAnswerNumber() {
    const number = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
    const answerNumberArray = [];

    for (let i = 10; i > 7; i--) {
        const pickNum = Math.floor(Math.random() * i);
        answerNumberArray.push(number[pickNum]);
        number.splice(pickNum, 1);
    }

    return answerNumberArray;
}

function CheckInputFormat(userArr) {
    let checkInputForm = true;

    if (userArr.length != 3) {
        checkInputForm = false;
    } else {
        for (let i = 0; i < 3; i++) {
            if (userArr[i].length != 1 || !isNumeric(userArr[i])) {
                checkInputForm = false;
            } else if (i != 0 && userArr[i - 1] == userArr[i]) {
                checkInputForm = false;
            }
        }
    }

    return checkInputForm;
}

function InputGuidePrint() {
    console.log("---------------------입력 안내--------------------------")
    console.log("* 입력은 공백을 구분으로 세 개의 숫자를 입력받습니다.");
    console.log("* 숫자는 0부터 9 사이의 양의 자연수입니다.");
    console.log("* 중복 입력은 허용하지 않습니다. ex) 1 1 2 => 1의 중복 입력");
    console.log("* 'give up'을 입력 시에 게임을 포기하는 것으로 간주하고 답을 출력합니다.\n");

    console.log("> 옳은 값으로 다시 입력해 주세요.")
}

function CompareUserNumberAndAnswerNumber(answerArr, userArr) {
    let checkAnswer = true;
    let strike = 0;
    let ball = 0;

    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (parseInt(userArr[i]) == answerArr[j] && i == j) {
                strike++;
            } else if (parseInt(userArr[i]) == answerArr[j] && i != j) {
                ball++;
            }
        }
    }

    PrintCompareResult(strike, ball);

    if (strike != 3) {
        checkAnswer = false;
    }

    return checkAnswer;
}

function isNumeric(val) {
    return /^-?\d+$/.test(val);
}

function PrintCompareResult(printStrike, printBall) {
    if (counterTime == 1 && printStrike == 3) { // 1회차 만에 맞혔을 경우
        console.log("!! 홈------런 !!");
    } else if (counterTime > 1 && printStrike == 3) { // 정답을 맞혔을 경우
        console.log(`✔ ${counterTime}회차 도전에 정답을 맞히셨습니다!`);
    } else if (s == 0 && b == 0) { // 아웃일 경우
        console.log(`✔ ${counterTime}회차 도전 결과 : OUT!!\n`)
    } else {
        console.log(`✔ ${counterTime}회차 도전 결과 : ${printStrike}S ${printBall}B\n`);
    }
}