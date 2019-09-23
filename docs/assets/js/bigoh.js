var cur = 0;
var res;
var errs;
var chart = null;
var ctx;

var ast = {};
var vars = [];

function peek(tokens) {
  skipTill(tokens);
  if (cur >= tokens.length) return null;
  return tokens[cur];
}

function next(tokens) {
  skipTill(tokens);
  if (cur >= tokens.length) return null;
  return tokens[cur++];
}

function skipTill(tokens) {
  while (cur < tokens.length && tokens[cur] == ';') cur++;
}

function requireTok(tokens, req) {
  tmp = next(tokens);
  if (!req.includes(tmp)) {
    errs.innerHTML = "Error was expecting one of '" + req + "'" + " got " + tmp;
    throw new Error();
  }
}

function addFor(tokens, ast) {
  ast.type = "for";
  requireTok(tokens, ["for"]);
  requireTok(tokens, ["all", "each"]);
  let var_name = next(tokens);
  ast.var_name = var_name;
  requireTok(tokens, ["=", "is"]);
  ast.start = {};
  parseAdditiveExpr(tokens, ast.start);
  let dir = peek(tokens);
  if (dir != "down" && dir != "up") {
    // the dir could be '..' in which case we presume it goes up
    if (dir == ".." || dir == "->" || dir == "...") {
      dir = "up";
    } else {
      requireTok(tokens, ["down to", "up to", "->", "..", "..."])
    }
    next(tokens);
  } else {
    next(tokens);
    requireTok(tokens, ["to"]);
  }
  ast.end = {};
  parseAdditiveExpr(tokens, ast.end);
  requireTok(tokens, ["do", "then"]);
  ast.dir = dir;
  parseOuter(tokens, ast);
  if (peek(tokens) == "end") {
    cur++;
    requireTok(tokens, ["for"]);
  } else {
    requireTok(tokens, ["endfor", "next"]);
  }
}

function addWhile(tokens, ast) {
  ast.type = "while";
  ast.cond = {};
  requireTok(tokens, ["while"]);
  parseLogicalOrExpr(tokens, ast.cond);
  requireTok(tokens, ["do", "then"]);
  ast.block = {};
  parseOuter(tokens, ast);

  if (peek(tokens) == "end") {
    cur++;
    requireTok(tokens, ["while", "endwhile"]);
  } else {
    requireTok(tokens, ["end", "endwhile"]);
  }
}

function addIf(tokens, ast) {
  ast.type = "if";
  ast.cond = {};
  requireTok(tokens, ["if", "elif"]);
  parseLogicalOrExpr(tokens, ast.cond);
  requireTok(tokens, ["then"]);
  ast.block = {};
  parseOuter(tokens, ast);
  if (peek(tokens) == "elif") {
    ast.elif = {};
    addIf(tokens, ast.elif);
  } else if (peek(tokens) == "else") {
    next(tokens);
    if (peek(tokens) == "if") {
      ast.elif = {};
      addIf(tokens, ast.elif);
    } else {
      ast.else = {"block": {}};
      ast.else.type = "Outer";
      parseOuter(tokens, ast.else);
      if (peek(tokens) == "end") {
        cur++;
        requireTok(tokens, ["if"]);
      } else {
        requireTok(tokens, ["endif"]);
      }
    }
  } else if (peek(tokens) == "end") {
    next(tokens);
    requireTok(tokens, ["if"]);
  } else {
    requireTok(tokens, ["endif"]);
  }
}

keywords = ["endfor", "else", "elif", "endif", "endwhile", "done", "next", "end", "for", "while", "if", "then"]
valid_calls = ["print", "pop", "enqueue", "push", "dequeue", "rand", "empty", "length", "floor", "ceil", "abs", "sort"]
calls = {
  "print": ((val) => {;}),
  "pop": ((from) => { return from.value.pop(); }),
  "push": ((elem, to) => { to.value.push(elem); }),
  "rand": ((len) => { if (len == undefined) { return {"value": Math.floor(Math.random() * 40) }; } else { return {"value": Array.from({length: len.value }, () => {return {"value": Math.floor(Math.random() * 40)};})};} }),
  "empty": ((from) => {return {"value": from.value.length == 0};}),
  "length": ((from) => {return {"value": from.value.length};}),
  "enqueue": ((elem, to) => { to.value.push(elem); }),
  "dequeue": ((from) => { return from.value.shift(); }),
  "floor": ((val) => { return {"value": Math.floor(val.value)}; }),
  "ceil": ((val) => { return {"value": Math.floor(val.value)}; }),
  "abs": ((val) => { return {"value": Math.abs(val.value)}; } ),
  "sort": ((val) => { val.value.sort((a, b) => a.value - b.value); })
}

function parseCall(tokens, ast) {
  name = next(tokens);
  ast.block = {};
  if (valid_calls.includes(name)) {
    ast.block.name = name;
    ast.type = "call";
    if (peek(tokens) != '(') {
      ast.block.args = [];
      while (cur < tokens.length && tokens[cur] != ';' && (cur == 0 || tokens[cur - 1] != ';') && !keywords.includes(tokens[cur])) {
        ast.block.args.push({});
        parseLogicalOrExpr(tokens, ast.block.args[ast.block.args.length - 1]);
      }
    } else {
      next(tokens);
      ast.block.args = [];
      while (cur < tokens.length && tokens[cur] != ')') {
        ast.block.args.push({});
        parseLogicalOrExpr(tokens, ast.block.args[ast.block.args.length - 1]);
      }
      requireTok(tokens, ')');
    }
  } else {
    errs.innerHTML = "Error: unknown call " + name;
    throw new Error();
  }
}

function parseLogicalOrExpr(tokens, ast) {
  ast.type = "Or";
  ast.block = [];
  while (true) {
    ast.block.push({});
    parseLogicalAndExpr(tokens, ast.block[ast.block.length - 1]);
    if (peek(tokens) != "||" && peek(tokens) != "or") {
      break;
    } else {
      next(tokens);
    }
  }

  if (ast.block.length == 1) {
    ast.type = ast.block[0].type;
    ast.block = ast.block[0].block;
  }
}

function parseLogicalAndExpr(tokens, ast) {
  ast.type = "And";
  ast.block = [];
  while (true) {
    ast.block.push({});
    parseComparisonExpr(tokens, ast.block[ast.block.length - 1]);
    if (peek(tokens) != "&&" && peek(tokens) != "and") {
      break;
    } else {
      next(tokens);
    }
  }

  if (ast.block.length == 1) {
    ast.type = ast.block[0].type;
    ast.block = ast.block[0].block;
  }
}

cmpTokens = ["<", ">", "=", "==", "!=", "~=", "<=", ">="];
function parseComparisonExpr(tokens, ast) {
  ast.type = "Cmp";
  ast.block = {};
  ast.block.lhs = {};
  parseAdditiveExpr(tokens, ast.block.lhs)

  if (cmpTokens.includes(peek(tokens))) {
    ast.block.op = next(tokens);
    ast.block.rhs = {};
    parseAdditiveExpr(tokens, ast.block.rhs);
  } else {
    ast.type = ast.block.lhs.type;
    ast.block = ast.block.lhs.block;
  }
}

addTokens = ["+", "-"]
function parseAdditiveExpr(tokens, ast) {
  ast.type = "Add";
  ast.block = {};
  ast.block.lhs = {};
  parseMultiplicativeExpr(tokens, ast.block.lhs);

  if (addTokens.includes(peek(tokens))) {
    ast.block.op = next(tokens);
    ast.block.rhs = {};
    parseAdditiveExpr(tokens, ast.block.rhs);
  } else {
    ast.type = ast.block.lhs.type;
    ast.block = ast.block.lhs.block;
  }
}

mulTokens = ["*", "/", "%"]
function parseMultiplicativeExpr(tokens, ast) {
  ast.type = "Mul";
  ast.block = {};
  ast.block.lhs = {};
  parseUnaryExpr(tokens, ast.block.lhs);

  if (mulTokens.includes(peek(tokens))) {
    ast.block.op = next(tokens);
    ast.block.rhs = {};
    parseUnaryExpr(tokens, ast.block.rhs);
  } else {
    ast.type = ast.block.lhs.type;
    ast.block = ast.block.lhs.block;
  }
}

unaryTokens = ["!", "-", "+"]
function parseUnaryExpr(tokens, ast) {
  ast.type = "Unary";
  ast.block = {};
  ast.block.lhs = [];
  while (unaryTokens.includes(peek(tokens))) {
    ast.block.lhs.push(next(tokens));
  }

  if (ast.block.lhs.length == 0) {
    parsePowerExpr(tokens, ast);
  } else {
    ast.block.rhs = {};
    parsePowerExpr(tokens, ast.block.rhs);
  }
}

function parsePowerExpr(tokens, ast) {
  ast.type = "Pow";
  ast.block = [];
  while (true) {
    ast.block.push({});
    parseAtomExpr(tokens, ast.block[ast.block.length - 1]);
    if (peek(tokens) != "**" && peek(tokens) != "^") {
      break;
    } else {
      next(tokens);
    }
  }

  if (ast.block.length == 1) {
    ast.type = ast.block[0].type;
    ast.block = ast.block[0].block;
  }
}

function parseAtomExpr(tokens, ast) {
  if (peek(tokens) == '(') {
    next(tokens);
    parseLogicalOrExpr(tokens, ast);
    requireTok(tokens, [")"])
  } else if (isNaN(Number(peek(tokens)))) {
    // identifier / weird symbol
    // just pretend its identifier
    if (valid_calls.includes(peek(tokens))) {
      parseCall(tokens, ast);
    } else {
      // presume its just a symbol like 'i'
      name = next(tokens);
      ast.block = {};
      if (peek(tokens) == '[') {
        // index
        ast.type = "index";
        next(tokens);
        ast.block.lhs = name;
        ast.block.inner = {};
        parseLogicalOrExpr(tokens, ast.block.inner);
        requireTok(tokens, ["]"]);
      } else {
        ast.type = "var";
        ast.block.value = name;
      }
    }
  } else {
    // number
    num = Number(next(tokens));
    ast.type = "num";
    ast.block = {};
    ast.block.value = num;
  }
}

letTokens = ["+=", "-=", "=", "/=", "*=", "**=", "%="]
function parseExpression(tokens, ast) {
  ast.type = "Let";
  ast.block = {};
  ast.block.lhs = {};
  parseAdditiveExpr(tokens, ast.block.lhs)

  if ((ast.block.lhs.type == "index" || ast.block.lhs.type == "var") &&
      letTokens.includes(peek(tokens))) {
    ast.block.op = next(tokens);
    ast.block.rhs = {};
    parseLogicalOrExpr(tokens, ast.block.rhs);
  } else {
    ast.type = ast.block.lhs.type;
    ast.block = ast.block.lhs.block;
  }
}

function parseOuter(tokens, ast) {
  ast.block = [];
  while (true) {
    let tok = peek(tokens);
    if (tok == "for") {
      ast.block.push({});
      addFor(tokens, ast.block[ast.block.length - 1]);
    } else if (tok === "while") {
      ast.block.push({});
      addWhile(tokens, ast.block[ast.block.length - 1]);
    } else if (tok === "if") {
      ast.block.push({});
      addIf(tokens, ast.block[ast.block.length - 1]);
    } else if (!keywords.includes(tok) && tok != null) {
      ast.block.push({});
      parseExpression(tokens, ast.block[ast.block.length - 1]);
    } else {
      break;
    }
  }
}

function runAST(ast) {
  switch (ast.type) {
    case "Outer": {
      return [null, ast.block.reduce((prev, ast) => runAST(ast)[1] + prev, 0)];
    }
    case "for": {
      let iterations = 0;
      var [start, its] = runAST(ast.start);
      iterations += its;
      var [end, its] = runAST(ast.end);
      iterations += its;
      let name = ast.var_name;
      if (ast.dir == "down") {
        accumulation = 0;
        let tmp = vars[ast.var_name];
        for (let i = start.value; i >= end.value; i--) {
          accumulation += 2;
          vars[ast.var_name] = {"value": i};
          accumulation += ast.block.reduce((prev, ast) => runAST(ast)[1] + prev, 0);
        }
        vars[ast.var_name] = tmp;
        accumulation += 1;
        return [null, accumulation];
      } else {
        accumulation = 0;
        let tmp = vars[ast.var_name];
        for (let i = start.value; i <= end.value; i++) {
          accumulation += 2;
          vars[ast.var_name] = {"value": i};
          accumulation += ast.block.reduce((prev, ast) => runAST(ast)[1] + prev, 0);
        }
        vars[ast.var_name] = tmp;
        accumulation += 1;
        return [null, accumulation];
      }
    }
    case "while": {
      let iterations = 0;
      while (1) {
        var [cond, its] = runAST(ast.cond);
        iterations += its;
        if (!cond.value) {
          break;
        }
        iterations += ast.block.reduce((prev, ast) => runAST(ast)[1] + prev, 0);
      }
      return [null, iterations];
    }
    case "Let": {
      let [lhs, lhs_its] = runAST(ast.block.lhs);
      let [rhs, rhs_its] = runAST(ast.block.rhs);
      switch (ast.block.op) {
        case "=": {
          lhs.value = rhs.value;
          break;
        }
        case "+=": {
          lhs.value += rhs.value;
          break;
        }
        case "-=": {
          lhs.value -= rhs.value;
          break;
        }
        case "*=": {
          lhs.value *= rhs.value;
          break;
        }
        case "/=": {
          lhs.value /= rhs.value;
          break;
        }
        case "**=": {
          lhs.value **= rhs.value;
          break;
        }
        case "%=": {
          lhs.value %= rhs.value;
          break;
        }
      }
      return [lhs, lhs_its + rhs_its + 1];
    }
    case "if": {
      let [cond, its] = runAST(ast.cond);
      if (cond.value) {
        its += ast.block.reduce((prev, ast) => runAST(ast)[1] + prev, 0);
        return [null, its];
      } else if (ast.elif) {
        return runAST(ast.elif);
      } else if (ast.else) {
        return runAST(ast.else);
      }
    }
    case "num": {
      return [{"value": ast.block.value}, 0];
    }
    case "var": {
      if (!vars[ast.block.value]) {
        vars[ast.block.value] = {"value": null};
      }
      return [vars[ast.block.value], 0];
    }
    case "call": {
      let arg_values = [];
      let iterations = 0;
      ast.block.args.forEach(element => {
        let [res, its] = runAST(element);
        iterations += its;
        arg_values.push(res);
      });
      return [calls[ast.block.name](...arg_values), iterations];
    }
    case "Or": {
      let res = false;
      let iterations = 0;
      ast.block.forEach(element => {
        if (!res) {
          let [elem_res, its] = runAST(element);
          iterations += its;
          if (elem_res.value) {
            res = true;
          }
        }
      })
      return [{"value": res}, iterations];
    }
    case "And": {
      let res = true;
      let iterations = 0;
      ast.block.forEach(element => {
        if (res) {
          let [elem_res, its] = runAST(element);
          iterations += its;
          if (!elem_res.value) {
            res = false;
          }
        }
      })
      return [{"value": res}, iterations];
    }
    case "Cmp": {
      let [lhs, lhs_its] = runAST(ast.block.lhs);
      let [rhs, rhs_its] = runAST(ast.block.rhs);
      let val = 0;
      switch (ast.block.op) {
        case "<": { val = lhs.value < rhs.value; break; }
        case "<=": { val = lhs.value <= rhs.value; break; }
        case ">": { val = lhs.value > rhs.value; break; }
        case ">=": { val = lhs.value >= rhs.value; break; }
        case "=": case "==": { val = lhs.value == rhs.value; break; }
        case "!=": case "~=": { val = lhs.value != rhs.value; break; }
        default: return [undefined, 0];
      }
      return [{"value": val}, lhs_its + rhs_its]
    }
    case "Add": {
      let [lhs, lhs_its] = runAST(ast.block.lhs);
      let [rhs, rhs_its] = runAST(ast.block.rhs);
      let val = 0;
      switch (ast.block.op) {
        case "+": { val = lhs.value + rhs.value; break; }
        case "-": { val = lhs.value - rhs.value; break; }
        default: return [undefined, 0];
      }
      return [{"value": val}, lhs_its + rhs_its]
    }
    case "Mul": {
      let [lhs, lhs_its] = runAST(ast.block.lhs);
      let [rhs, rhs_its] = runAST(ast.block.rhs);
      let val = 0;
      switch (ast.block.op) {
        case "*": { val = lhs.value * rhs.value; break; }
        case "/": { val = lhs.value / rhs.value; break; }
        case "%": { val = lhs.value % rhs.value; break; }
        default: return [undefined, 0];
      }
      return [{"value": val}, lhs_its + rhs_its]
    }
    case "Unary": {
      let [rhs, rhs_its] = runAST(ast.block.rhs);
      var tmp = rhs.value;
      ast.block.lhs.forEach(elem => {
        switch (elem) {
          case "-": { tmp = -tmp; break; }
          case "+": { tmp = +tmp; break; }
          case "!": { tmp = !tmp; break; }
        }
      });
      return [{"value": tmp}, rhs_its + ast.block.lhs.length];
    }
    case "Pow": {
      let [rhs, rhs_its] = runAST(ast.block[0]);
      ast.block.splice(1).forEach(elem => {
        let [tmp, its] = runAST(elem);
        rhs_its += its;
        rhs = rhs.value ** tmp.value;
      });
      return [rhs, rhs_its];
    }
    case "index": {
      let [index, its] = runAST(ast.block.inner);
      return [vars[ast.block.lhs].value[index.value], its + 1];
    }
  }
  return [null, 0];
}

function switchExample(num) {
  switch (num) {
    case 0: {
      document.getElementById("inputScript").value =
`A = rand n
for all i = n down to 1 do
  for all j = n down to i do
    print A[i] A[j]
  endfor
endfor`;
      break;
    }
    case 1: {
      document.getElementById("inputScript").value =
`A = rand n
currentMax=A[0]
for all i=1..n-1 do
  if A[i] > currentMax then
    currentMax=A[i]
  end if
end for`;
      break;
    }
    case 2: {
      document.getElementById("inputScript").value =
`A = rand n
sort A
goal = 5
lo = 0
hi = n - 1
ans = -1
while lo <= hi do
  m = floor((hi + lo) / 2)
  if abs(A[m] - goal) < 0.01 then
    ans = m
    lo = hi + 1
  elif A[m] > goal then
    hi = m - 1
  else
    lo = m + 1
  end if
end while`;
      break;
    }
    case 3: {
      document.getElementById("inputScript").value =
`A = rand n, B = rand n, k = rand
sum = 0, count = 0
C = rand 0
while sum <= k and !empty(A) do
  v = pop A, push v C
  sum += v, count += 1
end while

if sum > k then
  v = pop C
  sum -= v, count -= 1
end if
best = count

while !empty(B) do
  v = pop B
  sum += v, count += 1
  while sum > k and !empty(C) do
    v = pop C
    sum -= v, count -= 1
  end while

  if sum <= k and count > best then
    best = count
  end if
end while
`;
      break;
    }
    case 4: {
      document.getElementById("inputScript").value =
``;
      break;
    }
    case 5: {
      document.getElementById("inputScript").value =
``;
      break;
    }
  }
}

function run() {
  text = document.getElementById("inputScript").value;
  res = document.getElementById("result");
  errs = document.getElementById("error");
  errs.innerHTML = "";
  cur = 0;
  tokens = text.split("\n").join(";").split(',').join(";")
    .match(/([a-z|A-Z|_][a-z|A-Z|0-9|_]*|;|\(|\)|\[|\]|!=|==|=|%=|>=|<=|\.\.|\.\.\.|\-\>|\*=|\+=|\*\*=|\/=|>|<|\+|\-|\/|\*|%|\*\*|!|~=|\|\||&&|(\d*[\.]?\d+)|[.]\d+)/g)
    .map(i => i.trim()).filter(i => i);
  console.log("Parsing: [" + tokens + "]");
  ast = {};
  ast.type = "Outer";
  parseOuter(tokens, ast);
  console.table(ast);

  runData = [];
  run_labels = [];
  general = [
  {
    "name": "Program that was run",
    "func": (val => {
      vars = {"n": {"value": val}};
      return runAST(ast)[1];
    }),
    "color": "Grey",
    "disabled": false,
    "results": [],
    "cubic": "default"
  },
  {
    "name": "O(n^3)",
    "func": (val => val ** 3),
    "color": "Pink",
    "disabled": true,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(n^2.5)",
    "func": (val => val ** 2.5),
    "color": "Yellow",
    "disabled": true,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(n^2)",
    "func": (val => val ** 2),
    "color": "Red",
    "disabled": false,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(n)",
    "func": (val => val),
    "color": "Blue",
    "disabled": false,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(n log(n))",
    "func": (val => val * Math.log2(val)),
    "color": "Green",
    "disabled": false,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(log(n))",
    "func": (val => Math.log2(val)),
    "color": "Purple",
    "disabled": false,
    "results": [],
    "cubic": "monotone"
  },
  {
    "name": "O(1)",
    "func": (() => 1),
    "color": "Black",
    "disabled": false,
    "results": [],
    "cubic": "monotone"
  }]
  let start = document.getElementById("start").value;
  let stop = document.getElementById("end").value;
  let step = document.getElementById("step").value;

  for (val = start; val < stop; val *= step) {
    run_labels.push("" + val);
    general.forEach(element => {
      element.results.push(element.func(val));
    });
  }

  // eval at 10000 this should be not slow enough
  let eval_high = general.map(elem => { return { "name": elem.name, "res": elem.func(1000)} } );
  let max = Math.max.apply(Math, [].concat.apply([], general.map(elem => elem.results)))
  console.log(max);
  let closest = 0;

  let eval_next_high = general.map(elem => { return { "name": elem.name, "res": elem.func(50)} } );
  if (eval_high[0].res == eval_next_high[0].res) {
    closest = eval_high[eval_high.length - 1]
  } else {
    let goal = eval_high[0].res;
    closest = eval_high.slice(1).reduce((prev, cur) => {
      prev_v = prev.res;
      cur_v = cur.res;
      return Math.abs(cur_v - goal) < Math.abs(prev_v - goal) ? cur : prev;
    })
  }

  console.log("Closest is " + closest.name);
  document.getElementById("BigO").innerHTML = "I think the complexity is " + closest.name;
  general.forEach(elem => {elem.disabled = closest.name != elem.name && elem.name != general[0].name});

  let datasets = general.map(elem => {
    return {
      "label": elem.name,
      "borderColor": elem.color,
      "data": elem.results,
      "cubicInterpolationMode": elem.cubic,
      "hidden": elem.disabled
    };
  })

  ctx = document.getElementById('chart').getContext('2d');
  if (chart != null) chart.destroy();
  chart = new Chart(ctx, {
    type: 'line',
    data: {
      labels: run_labels,
      datasets: datasets
    },
    options: {
      scales: {
        xAxes: [{
          display: true,
          scaleLabel: {
            display: true,
            labelString: 'n'
          },
          min: 0,
          max: stop
        }],
        yAxes: [{
          display: true,
          scaleLabel: {
            display: true,
            labelString: 'primitive operations'
          },
          min: 0,
          max: max
        }]
      },
      plugins: {
        zoom: {
          pan: {
            enabled: true,
            mode: 'xy',
      
            rangeMin: {
              x: 0,
              y: 0
            },
            rangeMax: {
              x: stop,
              y: max
            }
          },
      
          zoom: {
            enabled: true,
            drag: false,
            mode: 'y',
      
            rangeMin: {
              x: 0,
              y: 0
            },
            rangeMax: {
              x: stop,
              y: max
            },
      
            // Speed of zoom via mouse wheel
            // (percentage of zoom on a wheel event)
            speed: 0.1
          }
        }
      }
    }
});
}