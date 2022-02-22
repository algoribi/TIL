const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

class BaseballGame {

    inputUserNumber() {
        return new Promise(function (resolve, reject) {
            const answerNumberArray = MakeAnswerNumber();
            
            console.log("-------새 게임을 시작합니다!-------");
            console.log("> 숫자를 입력해 주세요.");
            
            rl.on('line', function (userInput) {
                const userNumber = userInput.split(' ');
                
                if (userInput == 'give up') {
                    console.log(`정답 : ${answerNumberArray}\n`);
                    resolve();
                } else if (!CheckInputFormat(userNumber)) {
                    InputGuidePrint();
                } else if (CompareUserNumberAndAnswerNumber(answerNumberArray, userNumber)) {
                    resolve();
                } else {
                    console.log("> 숫자를 입력해 주세요.");
                }
            });
        });
    }

}

GameStart();

async function GameStart() {
    GameTitlePrint();

    const playBaseballGame = new BaseballGame();
    await playBaseballGame
        .inputUserNumber()
        .then(() => {
            rl.pause();
            /*if (AskNewGame()) {
                console.log("t");
            } else {
                console.log("f");
            }*/
            rl.resume();
            // rl.prompt();
        })
        .catch(console.log);
    
    GameStart();
}

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

    if (strike == 3) {
        return true;
    } else {
        return false;
    }
}

function isNumeric(val) {
    return /^-?\d+$/.test(val);
}

function PrintCompareResult(strike, ball) {
    if (strike == 3) { // 정답을 맞혔을 경우
        console.log(`✔ 정답을 맞히셨습니다!`);
    } else if (strike == 0 && ball == 0) { // 아웃일 경우
        console.log(`✔ 도전 결과 : OUT!!\n`)
    } else {
        console.log(`✔ 도전 결과 : ${strike}S ${ball}B\n`);
    }
}

function AskNewGame() {
    console.log("----------게임 종료----------");
    console.log("* 새로운 게임을 진행하시겠습니까?");
    console.log("* Yes or No 를 입력해 주세요.");
    
    rl.on('line', function (userInput) {
        if (userInput == "Yes" || userInput == "yes") {
            rl.close();
            return true;
        } else if (userInput == "No" || userInput == "no") {
            rl.close();
            return false;
        } else {
            console.log("* 올바른 입력을 주세요! ('Yes' or 'No')");
        }
    });
}