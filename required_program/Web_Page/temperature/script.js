function checkSettingValue(){
    if(settingValue!=label.textContent.slice(0,-1))
    {
        settingValue = label.textContent.slice(0,-1);
        console.log(settingValue);
    }
}
var settingValue = -1, intervalTime = 250, setInterval1 = setInterval(checkSettingValue,intervalTime);



var xmlns1 = "http://www.w3.org/2000/svg",
    xlinkns1 = "http://www.w3.org/1999/xlink",
    select = function (s) {
        return document.querySelector(s);
    },
    selectAll = function (s) {
        return document.querySelectorAll(s);
    },
    liquid1 = selectAll('.liquid1'),
    tubeShine1 = select('.tubeShine1'),
    label1 = select('.label1'),
    follower1 = select('.follower1'),
    dragger1 = select('.dragger1'),
    dragTip1 = select('.dragTip1'),
    minDragY1 = -380,
    liquidId1 = 0,
    step1 = Math.abs(minDragY1 / 100),
    snap1 = Math.abs(minDragY1 / 10),
    followerVY1 = 0

// setting initial temperature value
minDragY1 = -7.6 * 20

TweenMax.set('svg', {
    visibility: 'visible'
})

TweenMax.set(dragTip1, {
    transformOrigin: '20% 50%'
})

var tl = new TimelineMax()
tl.staggerTo(liquid1, 0.7, {
    x: '-=200',
    ease: Linear.easeNone,
    repeat: -1
}, 0.9)

tl.time(100);

document.addEventListener("touchmove", function (event) {
    //event.preventDefault();
});
/*Draggable.create(dragger, { // This have a bug when i shoot above or below
 type:'y',
 bounds:{minY:minDragY, maxY:0},
 onDrag:onUpdate,
 throwProps:true,
 throwResistance:2300,
 onThrowUpdate:onUpdate,
 overshootTolerance:0,
 snap:function(value){
  //Use this to snap the values to steps of 10
  //return Math.round(value/snap) * snap
 }
})*/

function onUpdate1() {
    liquidId1 = Math.abs(Math.round(dragger1._gsTransform.y / step1));

    label1.textContent = liquidId1 + '°';
    TweenMax.to(liquid1, 1.3, {
        y: dragger1._gsTransform.y * 1.12,
        ease: Elastic.easeOut.config(1, 0.4)
    })

}

TweenMax.to(follower1, 1, {
    y: '+=0',
    repeat: -1,
    modifiers: {
        y: function (y, count) {
            followerVY1 += (dragger1._gsTransform.y - follower1._gsTransform.y) * 0.23;
            followerVY1 *= 0.69;
            return follower1._gsTransform.y + followerVY1;
        }
    }
})

TweenMax.to(dragTip1, 1, {
    rotation: '+=0',
    repeat: -1,
    modifiers: {
        rotation: function (rotation, count) {
            return rotation - followerVY1
        }
    }
})

TweenMax.to(label1, 1, {
    y: '+=0',
    repeat: -1,
    modifiers: {
        y: function (y, count) {
            return y - followerVY1 * 0.5
        }
    }
})


TweenMax.to(dragger1, 1.4, {
    y: minDragY1 / 2,
    onUpdate: onUpdate1,
    ease: Expo.easeInOut
})


//ScrubGSAPTimeline(tl);

// Use the function below to change the temperature value..
function Update1(value) {
    if (value > 100)
        value = 100;
    if (value < 0)
        value = 0;

    dragger1._gsTransform.y = -value * step1;
    liquidId1 = Math.abs(Math.round(dragger1._gsTransform.y / step1));

    label1.textContent = liquidId1 + '°';
    TweenMax.to(liquid1, 1.3, {
        y: dragger1._gsTransform.y * 1.12,
        ease: Elastic.easeOut.config(1, 0.4)
    })

    TweenMax.to(dragger1, 1.4, {
        y: -7.6 * value / 2,
        onUpdate: onUpdate1,
        ease: Expo.easeInOut
    })

}


var /*xmlns = "http://www.w3.org/2000/svg",
  xlinkns = "http://www.w3.org/1999/xlink",
  select = function(s) {
    return document.querySelector(s);
  },
  selectAll = function(s) {
    return document.querySelectorAll(s);
  },*/
    liquid = selectAll('.liquid'),
    tubeShine = select('.tubeShine'),
    label = select('.label'),
    follower = select('.follower'),
    dragger = select('.dragger'),
    dragTip = select('.dragTip'),
    minDragY = -380,
    liquidId = 0,
    step = Math.abs(minDragY / 100),
    snap = Math.abs(minDragY / 10),
    followerVY = 0

// setting initial temperature value
minDragY = -7.6 * 40

TweenMax.set('svg', {
    visibility: 'visible'
})

TweenMax.set(dragTip, {
    transformOrigin: '20% 50%'
})

var t = new TimelineMax()
t.staggerTo(liquid, 0.7, {
    x: '-=200',
    ease: Linear.easeNone,
    repeat: -1
}, 0.9)

t.time(100);

document.addEventListener("touchmove", function (event) {
    //event.preventDefault();
});
Draggable.create(dragger, { // This have a bug when i shoot above or below
    type: 'y',
    bounds: { minY: minDragY, maxY: 0 },
    onDrag: onUpdate,
    throwProps: true,
    throwResistance: 2300,
    onThrowUpdate: onUpdate,
    overshootTolerance: 0,
    snap: function (value) {
        //Use this to snap the values to steps of 10
        //return Math.round(value/snap) * snap
    }
})

function onUpdate() {
    liquidId = Math.abs(Math.round(dragger._gsTransform.y / step));

    label.textContent = liquidId + '°';
    TweenMax.to(liquid, 1.3, {
        y: dragger._gsTransform.y * 1.12,
        ease: Elastic.easeOut.config(1, 0.4)
    })

    clearInterval(setInterval1);
    setInterval1 = setInterval(checkSettingValue,intervalTime);
}

TweenMax.to(follower, 1, {
    y: '+=0',
    repeat: -1,
    modifiers: {
        y: function (y, count) {
            followerVY += (dragger._gsTransform.y - follower._gsTransform.y) * 0.23;
            followerVY *= 0.69;
            return follower._gsTransform.y + followerVY;
        }
    }
})

TweenMax.to(dragTip, 1, {
    rotation: '+=0',
    repeat: -1,
    modifiers: {
        rotation: function (rotation, count) {
            return rotation - followerVY
        }
    }
})

TweenMax.to(label, 1, {
    y: '+=0',
    repeat: -1,
    modifiers: {
        y: function (y, count) {
            return y - followerVY * 0.5
        }
    }
})


TweenMax.to(dragger, 1.4, {
    y: minDragY / 2,
    onUpdate: onUpdate,
    ease: Expo.easeInOut
})


//ScrubGSAPTimeline(tl);

// Use the function below to change the temperature value..
function Update(value) {
    if (value > 100)
        value = 100;
    if (value < 0)
        value = 0;

    dragger._gsTransform.y = -value * step;
    liquidId = Math.abs(Math.round(dragger._gsTransform.y / step));

    label.textContent = liquidId + '°';
    TweenMax.to(liquid, 1.3, {
        y: dragger._gsTransform.y * 1.12,
        ease: Elastic.easeOut.config(1, 0.4)
    })

    TweenMax.to(dragger, 1.4, {
        y: -7.6 * value / 2,
        onUpdate: onUpdate,
        ease: Expo.easeInOut
    })

}