var $bm_rt;
var amp, freq, decay, n, n, t, t, v;
try {
    amp = div(effect(Elastic: Rotation)(1), 200);
    freq = div(effect(Elastic: Rotation)(2), 30);
    decay = div(effect(Elastic: Rotation)(3), 10);
    $bm_rt = n = 0;
    if (numKeys > 0) {
        $bm_rt = n = nearestKey(time).index;
        if (key(n).time > time) {
            n--;    
        }
    }
    if (n == 0) {
        $bm_rt = t = 0;
    } else {
        $bm_rt = t = sub(time, key(n).time);
    }
    if (n > 0) {
        v = velocityAtTime(sub(key(n).time, div(thisComp.frameDuration, 10)));
            $bm_rt = sum(value, div(mul(mul(v, amp), Math.sin(mul(mul(mul(freq, t), 2), Math.PI))), Math.exp(mul(decay, t))));
    } else {
        $bm_rt = value;
    }
} catch (e$$4) {
    $bm_rt = value = value;
}

