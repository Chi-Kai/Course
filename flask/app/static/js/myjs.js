let $para = $('#para')
    let $plays = $('.plays');
    let clicknum = 1;
    let $content = $('.content');
    let initNumber = 0;
    let $yudicontent = $('#yudicontent');
    for (let i = 0; i < 30; i++) {
        let lefts = (Math.floor(Math.random() * 5 + 2));
        let delay = (Math.floor(Math.random() * 50 + 2));
        //delays += delay;
        initNumber += lefts;
        let $div = $('<div>').addClass('yudi').css({
            "animation-delay": `${delay / 10}s`,
            "left": `${initNumber}%`,
            "top": `${lefts}%`

        });
        $yudicontent.append($div);
    }
    $(".content").click(function () {
        clicknum++;
        console.log("total点击了" + clicknum + "次");
    });
    function upplay() {
        let e = event || window.event;
        let yy = e.clientY;
        let xx = e.clientX;
        let top = yy - 80;
        let left = xx - 25;
        console.log(top);
        console.log(left);
        // let a1 = "富强";
        // let a2 = "民主";
        // let a3 = "文明";
        // let a4 = "和谐";
        //调试 console.log("？？？？？？？？？");
        if (clicknum % 4 == 1) {
            let $tag = "<p> 圣诞快乐! </p>";
            let $div2 = $('<div2>');
            $div2.prepend($tag);
            $div2.addClass('play');
            $div2.css({ top: top, left: left });

            $plays.append($div2);
            //调试  console.warn("sss");
        }
        else if (clicknum % 4 == 2) {
            let $tag = "<p> Merry Christmas!</p>";
            let $div2 = $('<div2>');
            $div2.prepend($tag);
            $div2.addClass('play');
            $div2.css({ top: top, left: left });

            $plays.append($div2);
        }
        else if (clicknum % 4 == 3) {
            let $tag = "<p> メリークリスマス!</p>";
            let $div2 = $('<div2>');
            $div2.prepend($tag);
            $div2.addClass('play');
            $div2.css({ top: top, left: left });

            $plays.append($div2);
        }
        else if (clicknum % 4 == 0) {
            let $tag = "<p> 聖誕快樂!</p>";
            let $div2 = $('<div2>');
            $div2.prepend($tag);
            $div2.addClass('play');
            $div2.css({ top: top, left: left });
            $plays.append($div2);
        }

    }