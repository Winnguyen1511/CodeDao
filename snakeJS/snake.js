const defaultW = 10;
const defaultH = 10;

class node {
    constructor(x, y, color){
        this._x = x;
        this._y = y;
        this._color = color;
    }
    get x()
    {
        return this._x;
    }
    set x(val)
    {
        this._x = val;
    }
    get y()
    {
        return this._y;
    }
    set y(val)
    {
        this._y = val;
    }
    get color()
    {
        return this._color;
    }
    set color(val)
    {
        this._color = val;
    }
    // move(dx_factor, dy_factor)
    // {
    //     this._dx = dx_factor * defaultW;
    //     this._dy = dy_factor * defaultH;
    // }
    // update()
    // {
    //     this._x = (this._x + this._dx + canvasWidth) % canvasWidth;
    //     this._y = (this._y + this._dy + canvasHeight) % canvasHeight;
    // }
    draw() {
        fill(this._color[0], this._color[1], this._color[2]);
        rect(this._x, this._y, defaultW, defaultH)
    }
}
class Snake
{
    constructor(node){
        this._color = node._color;
        this._body = [node];
        this._len  = 1;
        this._dx = 10;
        this._dy = 0;
    }
    move(dx_factor, dy_factor)
    {
        if(this._len > 1)
        {
            let tmpdx = dx_factor * defaultW;
            let tmpdy = dy_factor * defaultH;
            if(this._dx != -tmpdx)
            {
                this._dx = tmpdx;
            }
            if(this._dy != -tmpdy)
            {
                this._dy = tmpdy;
            }
        }
        else{
            this._dx = dx_factor * defaultW;
            this._dy = dy_factor * defaultH;
        }
    }
    update()
    {
        for(let i = 1; i < this._len ;i++)
        {
            if(this._body[0].x == this._body[i].x &&
                this._body[0].y == this._body[i].y)
            {
                return false;
            }
        }
        var newX = (this._body[0].x + this._dx + canvasWidth) % canvasWidth;
        var newY = (this._body[0].y + this._dy + canvasHeight) % canvasHeight;
        var newNode = new node(newX, newY, this._color);
        this._body.pop();
        this._body.unshift(newNode);
        return true;
    }
    eat(food)
    {
        if(this._body[0].x == food.x && this._body[0].y == food.y)
        {
            var newX = (this._body[0].x + this._dx + canvasWidth) % canvasWidth;
            var newY = (this._body[0].y + this._dy + canvasHeight) % canvasHeight;
            var newNode = new node(newX, newY, this._color);
            // this._body.pop();
            this._body.unshift(newNode);
            this._len++;
            return true;
        }
        return false;
    }
    draw()
    {
        for(let i = 0; i < this._len; i++)
        {
            this._body[i].draw();
        }
    }
}
