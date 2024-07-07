var Color;
/******/ (function() { // webpackBootstrap
/******/ 	var __webpack_modules__ = ([
/* 0 */,
/* 1 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(2);
/* harmony import */ var _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(3);



/**
 * Contains functions for checking that supplied arguments are of a specified type
 * or meet specified conditions
 */
const Check = {};

/**
 * Contains type checking functions, all using the typeof operator
 */
Check.typeOf = {};

function getUndefinedErrorMessage(name) {
  return `${name} is required, actual value was undefined`;
}

function getFailedTypeErrorMessage(actual, expected, name) {
  return `Expected ${name} to be typeof ${expected}, actual typeof was ${actual}`;
}

/**
 * Throws if test is not defined
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value that is to be checked
 * @exception {DeveloperError} test must be defined
 */
Check.defined = function (name, test) {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(test)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](getUndefinedErrorMessage(name));
  }
};

/**
 * Throws if test is not typeof 'function'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'function'
 */
Check.typeOf.func = function (name, test) {
  if (typeof test !== "function") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "function", name)
    );
  }
};

/**
 * Throws if test is not typeof 'string'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'string'
 */
Check.typeOf.string = function (name, test) {
  if (typeof test !== "string") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "string", name)
    );
  }
};

/**
 * Throws if test is not typeof 'number'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'number'
 */
Check.typeOf.number = function (name, test) {
  if (typeof test !== "number") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "number", name)
    );
  }
};

/**
 * Throws if test is not typeof 'number' and less than limit
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @param {number} limit The limit value to compare against
 * @exception {DeveloperError} test must be typeof 'number' and less than limit
 */
Check.typeOf.number.lessThan = function (name, test, limit) {
  Check.typeOf.number(name, test);
  if (test >= limit) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      `Expected ${name} to be less than ${limit}, actual value was ${test}`
    );
  }
};

/**
 * Throws if test is not typeof 'number' and less than or equal to limit
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @param {number} limit The limit value to compare against
 * @exception {DeveloperError} test must be typeof 'number' and less than or equal to limit
 */
Check.typeOf.number.lessThanOrEquals = function (name, test, limit) {
  Check.typeOf.number(name, test);
  if (test > limit) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      `Expected ${name} to be less than or equal to ${limit}, actual value was ${test}`
    );
  }
};

/**
 * Throws if test is not typeof 'number' and greater than limit
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @param {number} limit The limit value to compare against
 * @exception {DeveloperError} test must be typeof 'number' and greater than limit
 */
Check.typeOf.number.greaterThan = function (name, test, limit) {
  Check.typeOf.number(name, test);
  if (test <= limit) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      `Expected ${name} to be greater than ${limit}, actual value was ${test}`
    );
  }
};

/**
 * Throws if test is not typeof 'number' and greater than or equal to limit
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @param {number} limit The limit value to compare against
 * @exception {DeveloperError} test must be typeof 'number' and greater than or equal to limit
 */
Check.typeOf.number.greaterThanOrEquals = function (name, test, limit) {
  Check.typeOf.number(name, test);
  if (test < limit) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      `Expected ${name} to be greater than or equal to ${limit}, actual value was ${test}`
    );
  }
};

/**
 * Throws if test is not typeof 'object'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'object'
 */
Check.typeOf.object = function (name, test) {
  if (typeof test !== "object") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "object", name)
    );
  }
};

/**
 * Throws if test is not typeof 'boolean'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'boolean'
 */
Check.typeOf.bool = function (name, test) {
  if (typeof test !== "boolean") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "boolean", name)
    );
  }
};

/**
 * Throws if test is not typeof 'bigint'
 *
 * @param {string} name The name of the variable being tested
 * @param {*} test The value to test
 * @exception {DeveloperError} test must be typeof 'bigint'
 */
Check.typeOf.bigint = function (name, test) {
  if (typeof test !== "bigint") {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      getFailedTypeErrorMessage(typeof test, "bigint", name)
    );
  }
};

/**
 * Throws if test1 and test2 is not typeof 'number' and not equal in value
 *
 * @param {string} name1 The name of the first variable being tested
 * @param {string} name2 The name of the second variable being tested against
 * @param {*} test1 The value to test
 * @param {*} test2 The value to test against
 * @exception {DeveloperError} test1 and test2 should be type of 'number' and be equal in value
 */
Check.typeOf.number.equals = function (name1, name2, test1, test2) {
  Check.typeOf.number(name1, test1);
  Check.typeOf.number(name2, test2);
  if (test1 !== test2) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      `${name1} must be equal to ${name2}, the actual values are ${test1} and ${test2}`
    );
  }
};
/* harmony default export */ __webpack_exports__["default"] = (Check);


/***/ }),
/* 2 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/**
 * @function
 *
 * @param {*} value The object.
 * @returns {boolean} Returns true if the object is defined, returns false otherwise.
 *
 * @example
 * if (Cesium.defined(positions)) {
 *      doSomething();
 * } else {
 *      doSomethingElse();
 * }
 */
function defined(value) {
  return value !== undefined && value !== null;
}
/* harmony default export */ __webpack_exports__["default"] = (defined);


/***/ }),
/* 3 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(2);


/**
 * Constructs an exception object that is thrown due to a developer error, e.g., invalid argument,
 * argument out of range, etc.  This exception should only be thrown during development;
 * it usually indicates a bug in the calling code.  This exception should never be
 * caught; instead the calling code should strive not to generate it.
 * <br /><br />
 * On the other hand, a {@link RuntimeError} indicates an exception that may
 * be thrown at runtime, e.g., out of memory, that the calling code should be prepared
 * to catch.
 *
 * @alias DeveloperError
 * @constructor
 * @extends Error
 *
 * @param {string} [message] The error message for this exception.
 *
 * @see RuntimeError
 */
function DeveloperError(message) {
  /**
   * 'DeveloperError' indicating that this exception was thrown due to a developer error.
   * @type {string}
   * @readonly
   */
  this.name = "DeveloperError";

  /**
   * The explanation for why this exception was thrown.
   * @type {string}
   * @readonly
   */
  this.message = message;

  //Browsers such as IE don't have a stack property until you actually throw the error.
  let stack;
  try {
    throw new Error();
  } catch (e) {
    stack = e.stack;
  }

  /**
   * The stack trace of this exception, if available.
   * @type {string}
   * @readonly
   */
  this.stack = stack;
}

if ((0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(Object.create)) {
  DeveloperError.prototype = Object.create(Error.prototype);
  DeveloperError.prototype.constructor = DeveloperError;
}

DeveloperError.prototype.toString = function () {
  let str = `${this.name}: ${this.message}`;

  if ((0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(this.stack)) {
    str += `\n${this.stack.toString()}`;
  }

  return str;
};

/**
 * @private
 */
DeveloperError.throwInstantiationError = function () {
  throw new DeveloperError(
    "This function defines an interface and should not be called directly."
  );
};
/* harmony default export */ __webpack_exports__["default"] = (DeveloperError);


/***/ }),
/* 4 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/**
 * Returns the first parameter if not undefined, otherwise the second parameter.
 * Useful for setting a default value for a parameter.
 *
 * @function
 *
 * @param {*} a
 * @param {*} b
 * @returns {*} Returns the first parameter if not undefined, otherwise the second parameter.
 *
 * @example
 * param = Cesium.defaultValue(param, 'default');
 */
function defaultValue(a, b) {
  if (a !== undefined && a !== null) {
    return a;
  }
  return b;
}

/**
 * A frozen empty object that can be used as the default value for options passed as
 * an object literal.
 * @type {object}
 * @memberof defaultValue
 */
defaultValue.EMPTY_OBJECT = Object.freeze({});

/* harmony default export */ __webpack_exports__["default"] = (defaultValue);


/***/ }),
/* 5 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Check_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(1);
/* harmony import */ var _defaultValue_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(4);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(2);
/* harmony import */ var _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(3);
/* harmony import */ var _Fullscreen_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(6);






let theNavigator;
if (typeof navigator !== "undefined") {
  theNavigator = navigator;
} else {
  theNavigator = {};
}

function extractVersion(versionString) {
  const parts = versionString.split(".");
  for (let i = 0, len = parts.length; i < len; ++i) {
    parts[i] = parseInt(parts[i], 10);
  }
  return parts;
}

let isChromeResult;
let chromeVersionResult;
function isChrome() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isChromeResult)) {
    isChromeResult = false;
    // Edge contains Chrome in the user agent too
    if (!isEdge()) {
      const fields = / Chrome\/([\.0-9]+)/.exec(theNavigator.userAgent);
      if (fields !== null) {
        isChromeResult = true;
        chromeVersionResult = extractVersion(fields[1]);
      }
    }
  }

  return isChromeResult;
}

function chromeVersion() {
  return isChrome() && chromeVersionResult;
}

let isSafariResult;
let safariVersionResult;
function isSafari() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isSafariResult)) {
    isSafariResult = false;

    // Chrome and Edge contain Safari in the user agent too
    if (
      !isChrome() &&
      !isEdge() &&
      / Safari\/[\.0-9]+/.test(theNavigator.userAgent)
    ) {
      const fields = / Version\/([\.0-9]+)/.exec(theNavigator.userAgent);
      if (fields !== null) {
        isSafariResult = true;
        safariVersionResult = extractVersion(fields[1]);
      }
    }
  }

  return isSafariResult;
}

function safariVersion() {
  return isSafari() && safariVersionResult;
}

let isWebkitResult;
let webkitVersionResult;
function isWebkit() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isWebkitResult)) {
    isWebkitResult = false;

    const fields = / AppleWebKit\/([\.0-9]+)(\+?)/.exec(theNavigator.userAgent);
    if (fields !== null) {
      isWebkitResult = true;
      webkitVersionResult = extractVersion(fields[1]);
      webkitVersionResult.isNightly = !!fields[2];
    }
  }

  return isWebkitResult;
}

function webkitVersion() {
  return isWebkit() && webkitVersionResult;
}

let isInternetExplorerResult;
let internetExplorerVersionResult;
function isInternetExplorer() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isInternetExplorerResult)) {
    isInternetExplorerResult = false;

    let fields;
    if (theNavigator.appName === "Microsoft Internet Explorer") {
      fields = /MSIE ([0-9]{1,}[\.0-9]{0,})/.exec(theNavigator.userAgent);
      if (fields !== null) {
        isInternetExplorerResult = true;
        internetExplorerVersionResult = extractVersion(fields[1]);
      }
    } else if (theNavigator.appName === "Netscape") {
      fields = /Trident\/.*rv:([0-9]{1,}[\.0-9]{0,})/.exec(
        theNavigator.userAgent
      );
      if (fields !== null) {
        isInternetExplorerResult = true;
        internetExplorerVersionResult = extractVersion(fields[1]);
      }
    }
  }
  return isInternetExplorerResult;
}

function internetExplorerVersion() {
  return isInternetExplorer() && internetExplorerVersionResult;
}

let isEdgeResult;
let edgeVersionResult;
function isEdge() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isEdgeResult)) {
    isEdgeResult = false;
    const fields = / Edg\/([\.0-9]+)/.exec(theNavigator.userAgent);
    if (fields !== null) {
      isEdgeResult = true;
      edgeVersionResult = extractVersion(fields[1]);
    }
  }
  return isEdgeResult;
}

function edgeVersion() {
  return isEdge() && edgeVersionResult;
}

let isFirefoxResult;
let firefoxVersionResult;
function isFirefox() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isFirefoxResult)) {
    isFirefoxResult = false;

    const fields = /Firefox\/([\.0-9]+)/.exec(theNavigator.userAgent);
    if (fields !== null) {
      isFirefoxResult = true;
      firefoxVersionResult = extractVersion(fields[1]);
    }
  }
  return isFirefoxResult;
}

let isWindowsResult;
function isWindows() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isWindowsResult)) {
    isWindowsResult = /Windows/i.test(theNavigator.appVersion);
  }
  return isWindowsResult;
}

let isIPadOrIOSResult;
function isIPadOrIOS() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(isIPadOrIOSResult)) {
    isIPadOrIOSResult =
      navigator.platform === "iPhone" ||
      navigator.platform === "iPod" ||
      navigator.platform === "iPad";
  }

  return isIPadOrIOSResult;
}

function firefoxVersion() {
  return isFirefox() && firefoxVersionResult;
}

let hasPointerEvents;
function supportsPointerEvents() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(hasPointerEvents)) {
    //While navigator.pointerEnabled is deprecated in the W3C specification
    //we still need to use it if it exists in order to support browsers
    //that rely on it, such as the Windows WebBrowser control which defines
    //PointerEvent but sets navigator.pointerEnabled to false.

    //Firefox disabled because of https://github.com/CesiumGS/cesium/issues/6372
    hasPointerEvents =
      !isFirefox() &&
      typeof PointerEvent !== "undefined" &&
      (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(theNavigator.pointerEnabled) || theNavigator.pointerEnabled);
  }
  return hasPointerEvents;
}

let imageRenderingValueResult;
let supportsImageRenderingPixelatedResult;
function supportsImageRenderingPixelated() {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(supportsImageRenderingPixelatedResult)) {
    const canvas = document.createElement("canvas");
    canvas.setAttribute(
      "style",
      "image-rendering: -moz-crisp-edges;" + "image-rendering: pixelated;"
    );
    //canvas.style.imageRendering will be undefined, null or an empty string on unsupported browsers.
    const tmp = canvas.style.imageRendering;
    supportsImageRenderingPixelatedResult = (0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(tmp) && tmp !== "";
    if (supportsImageRenderingPixelatedResult) {
      imageRenderingValueResult = tmp;
    }
  }
  return supportsImageRenderingPixelatedResult;
}

function imageRenderingValue() {
  return supportsImageRenderingPixelated()
    ? imageRenderingValueResult
    : undefined;
}

function supportsWebP() {
  //>>includeStart('debug', pragmas.debug);
  if (!supportsWebP.initialized) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_1__["default"](
      "You must call FeatureDetection.supportsWebP.initialize and wait for the promise to resolve before calling FeatureDetection.supportsWebP"
    );
  }
  //>>includeEnd('debug');
  return supportsWebP._result;
}
supportsWebP._promise = undefined;
supportsWebP._result = undefined;
supportsWebP.initialize = function () {
  // From https://developers.google.com/speed/webp/faq#how_can_i_detect_browser_support_for_webp
  if ((0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(supportsWebP._promise)) {
    return supportsWebP._promise;
  }

  supportsWebP._promise = new Promise((resolve) => {
    const image = new Image();
    image.onload = function () {
      supportsWebP._result = image.width > 0 && image.height > 0;
      resolve(supportsWebP._result);
    };

    image.onerror = function () {
      supportsWebP._result = false;
      resolve(supportsWebP._result);
    };
    image.src =
      "data:image/webp;base64,UklGRiIAAABXRUJQVlA4IBYAAAAwAQCdASoBAAEADsD+JaQAA3AAAAAA";
  });

  return supportsWebP._promise;
};
Object.defineProperties(supportsWebP, {
  initialized: {
    get: function () {
      return (0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(supportsWebP._result);
    },
  },
});

const typedArrayTypes = [];
if (typeof ArrayBuffer !== "undefined") {
  typedArrayTypes.push(
    Int8Array,
    Uint8Array,
    Int16Array,
    Uint16Array,
    Int32Array,
    Uint32Array,
    Float32Array,
    Float64Array
  );

  if (typeof Uint8ClampedArray !== "undefined") {
    typedArrayTypes.push(Uint8ClampedArray);
  }

  if (typeof Uint8ClampedArray !== "undefined") {
    typedArrayTypes.push(Uint8ClampedArray);
  }

  if (typeof BigInt64Array !== "undefined") {
    // eslint-disable-next-line no-undef
    typedArrayTypes.push(BigInt64Array);
  }

  if (typeof BigUint64Array !== "undefined") {
    // eslint-disable-next-line no-undef
    typedArrayTypes.push(BigUint64Array);
  }
}

/**
 * A set of functions to detect whether the current browser supports
 * various features.
 *
 * @namespace FeatureDetection
 */
const FeatureDetection = {
  isChrome: isChrome,
  chromeVersion: chromeVersion,
  isSafari: isSafari,
  safariVersion: safariVersion,
  isWebkit: isWebkit,
  webkitVersion: webkitVersion,
  isInternetExplorer: isInternetExplorer,
  internetExplorerVersion: internetExplorerVersion,
  isEdge: isEdge,
  edgeVersion: edgeVersion,
  isFirefox: isFirefox,
  firefoxVersion: firefoxVersion,
  isWindows: isWindows,
  isIPadOrIOS: isIPadOrIOS,
  hardwareConcurrency: (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_2__["default"])(theNavigator.hardwareConcurrency, 3),
  supportsPointerEvents: supportsPointerEvents,
  supportsImageRenderingPixelated: supportsImageRenderingPixelated,
  supportsWebP: supportsWebP,
  imageRenderingValue: imageRenderingValue,
  typedArrayTypes: typedArrayTypes,
};

/**
 * Detects whether the current browser supports Basis Universal textures and the web assembly modules needed to transcode them.
 *
 * @param {Scene} scene
 * @returns {boolean} true if the browser supports web assembly modules and the scene supports Basis Universal textures, false if not.
 */
FeatureDetection.supportsBasis = function (scene) {
  return FeatureDetection.supportsWebAssembly() && scene.context.supportsBasis;
};

/**
 * Detects whether the current browser supports the full screen standard.
 *
 * @returns {boolean} true if the browser supports the full screen standard, false if not.
 *
 * @see Fullscreen
 * @see {@link http://dvcs.w3.org/hg/fullscreen/raw-file/tip/Overview.html|W3C Fullscreen Living Specification}
 */
FeatureDetection.supportsFullscreen = function () {
  return _Fullscreen_js__WEBPACK_IMPORTED_MODULE_3__["default"].supportsFullscreen();
};

/**
 * Detects whether the current browser supports typed arrays.
 *
 * @returns {boolean} true if the browser supports typed arrays, false if not.
 *
 * @see {@link https://tc39.es/ecma262/#sec-typedarray-objects|Typed Array Specification}
 */
FeatureDetection.supportsTypedArrays = function () {
  return typeof ArrayBuffer !== "undefined";
};

/**
 * Detects whether the current browser supports BigInt64Array typed arrays.
 *
 * @returns {boolean} true if the browser supports BigInt64Array typed arrays, false if not.
 *
 * @see {@link https://tc39.es/ecma262/#sec-typedarray-objects|Typed Array Specification}
 */
FeatureDetection.supportsBigInt64Array = function () {
  return typeof BigInt64Array !== "undefined";
};

/**
 * Detects whether the current browser supports BigUint64Array typed arrays.
 *
 * @returns {boolean} true if the browser supports BigUint64Array typed arrays, false if not.
 *
 * @see {@link https://tc39.es/ecma262/#sec-typedarray-objects|Typed Array Specification}
 */
FeatureDetection.supportsBigUint64Array = function () {
  return typeof BigUint64Array !== "undefined";
};

/**
 * Detects whether the current browser supports BigInt.
 *
 * @returns {boolean} true if the browser supports BigInt, false if not.
 *
 * @see {@link https://tc39.es/ecma262/#sec-bigint-objects|BigInt Specification}
 */
FeatureDetection.supportsBigInt = function () {
  return typeof BigInt !== "undefined";
};

/**
 * Detects whether the current browser supports Web Workers.
 *
 * @returns {boolean} true if the browsers supports Web Workers, false if not.
 *
 * @see {@link http://www.w3.org/TR/workers/}
 */
FeatureDetection.supportsWebWorkers = function () {
  return typeof Worker !== "undefined";
};

/**
 * Detects whether the current browser supports Web Assembly.
 *
 * @returns {boolean} true if the browsers supports Web Assembly, false if not.
 *
 * @see {@link https://developer.mozilla.org/en-US/docs/WebAssembly}
 */
FeatureDetection.supportsWebAssembly = function () {
  return typeof WebAssembly !== "undefined";
};

/**
 * Detects whether the current browser supports a WebGL2 rendering context for the specified scene.
 *
 * @param {Scene} scene the Cesium scene specifying the rendering context
 * @returns {boolean} true if the browser supports a WebGL2 rendering context, false if not.
 *
 * @see {@link https://developer.mozilla.org/en-US/docs/Web/API/WebGL2RenderingContext|WebGL2RenderingContext}
 */
FeatureDetection.supportsWebgl2 = function (scene) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].defined("scene", scene);
  //>>includeEnd('debug');

  return scene.context.webgl2;
};

/**
 * Detects whether the current browser supports ECMAScript modules in web workers.
 * @returns {boolean} true if the browser supports ECMAScript modules in web workers.
 * @see {@link https://developer.mozilla.org/en-US/docs/Web/API/Worker|Worker}
 */
FeatureDetection.supportsEsmWebWorkers = function () {
  return !isFirefox() || parseInt(firefoxVersionResult) >= 114;
};

/* harmony default export */ __webpack_exports__["default"] = (FeatureDetection);


/***/ }),
/* 6 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(2);


let _supportsFullscreen;
const _names = {
  requestFullscreen: undefined,
  exitFullscreen: undefined,
  fullscreenEnabled: undefined,
  fullscreenElement: undefined,
  fullscreenchange: undefined,
  fullscreenerror: undefined,
};

/**
 * Browser-independent functions for working with the standard fullscreen API.
 *
 * @namespace Fullscreen
 *
 * @see {@link http://dvcs.w3.org/hg/fullscreen/raw-file/tip/Overview.html|W3C Fullscreen Living Specification}
 */
const Fullscreen = {};

Object.defineProperties(Fullscreen, {
  /**
   * The element that is currently fullscreen, if any.  To simply check if the
   * browser is in fullscreen mode or not, use {@link Fullscreen#fullscreen}.
   * @memberof Fullscreen
   * @type {object}
   * @readonly
   */
  element: {
    get: function () {
      if (!Fullscreen.supportsFullscreen()) {
        return undefined;
      }

      return document[_names.fullscreenElement];
    },
  },

  /**
   * The name of the event on the document that is fired when fullscreen is
   * entered or exited.  This event name is intended for use with addEventListener.
   * In your event handler, to determine if the browser is in fullscreen mode or not,
   * use {@link Fullscreen#fullscreen}.
   * @memberof Fullscreen
   * @type {string}
   * @readonly
   */
  changeEventName: {
    get: function () {
      if (!Fullscreen.supportsFullscreen()) {
        return undefined;
      }

      return _names.fullscreenchange;
    },
  },

  /**
   * The name of the event that is fired when a fullscreen error
   * occurs.  This event name is intended for use with addEventListener.
   * @memberof Fullscreen
   * @type {string}
   * @readonly
   */
  errorEventName: {
    get: function () {
      if (!Fullscreen.supportsFullscreen()) {
        return undefined;
      }

      return _names.fullscreenerror;
    },
  },

  /**
   * Determine whether the browser will allow an element to be made fullscreen, or not.
   * For example, by default, iframes cannot go fullscreen unless the containing page
   * adds an "allowfullscreen" attribute (or prefixed equivalent).
   * @memberof Fullscreen
   * @type {boolean}
   * @readonly
   */
  enabled: {
    get: function () {
      if (!Fullscreen.supportsFullscreen()) {
        return undefined;
      }

      return document[_names.fullscreenEnabled];
    },
  },

  /**
   * Determines if the browser is currently in fullscreen mode.
   * @memberof Fullscreen
   * @type {boolean}
   * @readonly
   */
  fullscreen: {
    get: function () {
      if (!Fullscreen.supportsFullscreen()) {
        return undefined;
      }

      return Fullscreen.element !== null;
    },
  },
});

/**
 * Detects whether the browser supports the standard fullscreen API.
 *
 * @returns {boolean} <code>true</code> if the browser supports the standard fullscreen API,
 * <code>false</code> otherwise.
 */
Fullscreen.supportsFullscreen = function () {
  if ((0,_defined_js__WEBPACK_IMPORTED_MODULE_0__["default"])(_supportsFullscreen)) {
    return _supportsFullscreen;
  }

  _supportsFullscreen = false;

  const body = document.body;
  if (typeof body.requestFullscreen === "function") {
    // go with the unprefixed, standard set of names
    _names.requestFullscreen = "requestFullscreen";
    _names.exitFullscreen = "exitFullscreen";
    _names.fullscreenEnabled = "fullscreenEnabled";
    _names.fullscreenElement = "fullscreenElement";
    _names.fullscreenchange = "fullscreenchange";
    _names.fullscreenerror = "fullscreenerror";
    _supportsFullscreen = true;
    return _supportsFullscreen;
  }

  //check for the correct combination of prefix plus the various names that browsers use
  const prefixes = ["webkit", "moz", "o", "ms", "khtml"];
  let name;
  for (let i = 0, len = prefixes.length; i < len; ++i) {
    const prefix = prefixes[i];

    // casing of Fullscreen differs across browsers
    name = `${prefix}RequestFullscreen`;
    if (typeof body[name] === "function") {
      _names.requestFullscreen = name;
      _supportsFullscreen = true;
    } else {
      name = `${prefix}RequestFullScreen`;
      if (typeof body[name] === "function") {
        _names.requestFullscreen = name;
        _supportsFullscreen = true;
      }
    }

    // disagreement about whether it's "exit" as per spec, or "cancel"
    name = `${prefix}ExitFullscreen`;
    if (typeof document[name] === "function") {
      _names.exitFullscreen = name;
    } else {
      name = `${prefix}CancelFullScreen`;
      if (typeof document[name] === "function") {
        _names.exitFullscreen = name;
      }
    }

    // casing of Fullscreen differs across browsers
    name = `${prefix}FullscreenEnabled`;
    if (document[name] !== undefined) {
      _names.fullscreenEnabled = name;
    } else {
      name = `${prefix}FullScreenEnabled`;
      if (document[name] !== undefined) {
        _names.fullscreenEnabled = name;
      }
    }

    // casing of Fullscreen differs across browsers
    name = `${prefix}FullscreenElement`;
    if (document[name] !== undefined) {
      _names.fullscreenElement = name;
    } else {
      name = `${prefix}FullScreenElement`;
      if (document[name] !== undefined) {
        _names.fullscreenElement = name;
      }
    }

    // thankfully, event names are all lowercase per spec
    name = `${prefix}fullscreenchange`;
    // event names do not have 'on' in the front, but the property on the document does
    if (document[`on${name}`] !== undefined) {
      //except on IE
      if (prefix === "ms") {
        name = "MSFullscreenChange";
      }
      _names.fullscreenchange = name;
    }

    name = `${prefix}fullscreenerror`;
    if (document[`on${name}`] !== undefined) {
      //except on IE
      if (prefix === "ms") {
        name = "MSFullscreenError";
      }
      _names.fullscreenerror = name;
    }
  }

  return _supportsFullscreen;
};

/**
 * Asynchronously requests the browser to enter fullscreen mode on the given element.
 * If fullscreen mode is not supported by the browser, does nothing.
 *
 * @param {object} element The HTML element which will be placed into fullscreen mode.
 * @param {object} [vrDevice] The HMDVRDevice device.
 *
 * @example
 * // Put the entire page into fullscreen.
 * Cesium.Fullscreen.requestFullscreen(document.body)
 *
 * // Place only the Cesium canvas into fullscreen.
 * Cesium.Fullscreen.requestFullscreen(scene.canvas)
 */
Fullscreen.requestFullscreen = function (element, vrDevice) {
  if (!Fullscreen.supportsFullscreen()) {
    return;
  }

  element[_names.requestFullscreen]({ vrDisplay: vrDevice });
};

/**
 * Asynchronously exits fullscreen mode.  If the browser is not currently
 * in fullscreen, or if fullscreen mode is not supported by the browser, does nothing.
 */
Fullscreen.exitFullscreen = function () {
  if (!Fullscreen.supportsFullscreen()) {
    return;
  }

  document[_names.exitFullscreen]();
};

//For unit tests
Fullscreen._names = _names;
/* harmony default export */ __webpack_exports__["default"] = (Fullscreen);


/***/ }),
/* 7 */
/***/ (function(__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var mersenne_twister__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(8);
/* harmony import */ var _Check_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(1);
/* harmony import */ var _defaultValue_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(4);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(2);
/* harmony import */ var _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(3);






/**
 * Math functions.
 *
 * @exports CesiumMath
 * @alias Math
 */
const CesiumMath = {};

/**
 * 0.1
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON1 = 0.1;

/**
 * 0.01
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON2 = 0.01;

/**
 * 0.001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON3 = 0.001;

/**
 * 0.0001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON4 = 0.0001;

/**
 * 0.00001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON5 = 0.00001;

/**
 * 0.000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON6 = 0.000001;

/**
 * 0.0000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON7 = 0.0000001;

/**
 * 0.00000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON8 = 0.00000001;

/**
 * 0.000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON9 = 0.000000001;

/**
 * 0.0000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON10 = 0.0000000001;

/**
 * 0.00000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON11 = 0.00000000001;

/**
 * 0.000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON12 = 0.000000000001;

/**
 * 0.0000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON13 = 0.0000000000001;

/**
 * 0.00000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON14 = 0.00000000000001;

/**
 * 0.000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON15 = 0.000000000000001;

/**
 * 0.0000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON16 = 0.0000000000000001;

/**
 * 0.00000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON17 = 0.00000000000000001;

/**
 * 0.000000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON18 = 0.000000000000000001;

/**
 * 0.0000000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON19 = 0.0000000000000000001;

/**
 * 0.00000000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON20 = 0.00000000000000000001;

/**
 * 0.000000000000000000001
 * @type {number}
 * @constant
 */
CesiumMath.EPSILON21 = 0.000000000000000000001;

/**
 * The gravitational parameter of the Earth in meters cubed
 * per second squared as defined by the WGS84 model: 3.986004418e14
 * @type {number}
 * @constant
 */
CesiumMath.GRAVITATIONALPARAMETER = 3.986004418e14;

/**
 * Radius of the sun in meters: 6.955e8
 * @type {number}
 * @constant
 */
CesiumMath.SOLAR_RADIUS = 6.955e8;

/**
 * The mean radius of the moon, according to the "Report of the IAU/IAG Working Group on
 * Cartographic Coordinates and Rotational Elements of the Planets and satellites: 2000",
 * Celestial Mechanics 82: 83-110, 2002.
 * @type {number}
 * @constant
 */
CesiumMath.LUNAR_RADIUS = 1737400.0;

/**
 * 64 * 1024
 * @type {number}
 * @constant
 */
CesiumMath.SIXTY_FOUR_KILOBYTES = 64 * 1024;

/**
 * 4 * 1024 * 1024 * 1024
 * @type {number}
 * @constant
 */
CesiumMath.FOUR_GIGABYTES = 4 * 1024 * 1024 * 1024;

/**
 * Returns the sign of the value; 1 if the value is positive, -1 if the value is
 * negative, or 0 if the value is 0.
 *
 * @function
 * @param {number} value The value to return the sign of.
 * @returns {number} The sign of value.
 */
CesiumMath.sign = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(Math.sign, function sign(value) {
  value = +value; // coerce to number
  if (value === 0 || value !== value) {
    // zero or NaN
    return value;
  }
  return value > 0 ? 1 : -1;
});

/**
 * Returns 1.0 if the given value is positive or zero, and -1.0 if it is negative.
 * This is similar to {@link CesiumMath#sign} except that returns 1.0 instead of
 * 0.0 when the input value is 0.0.
 * @param {number} value The value to return the sign of.
 * @returns {number} The sign of value.
 */
CesiumMath.signNotZero = function (value) {
  return value < 0.0 ? -1.0 : 1.0;
};

/**
 * Converts a scalar value in the range [-1.0, 1.0] to a SNORM in the range [0, rangeMaximum]
 * @param {number} value The scalar value in the range [-1.0, 1.0]
 * @param {number} [rangeMaximum=255] The maximum value in the mapped range, 255 by default.
 * @returns {number} A SNORM value, where 0 maps to -1.0 and rangeMaximum maps to 1.0.
 *
 * @see CesiumMath.fromSNorm
 */
CesiumMath.toSNorm = function (value, rangeMaximum) {
  rangeMaximum = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(rangeMaximum, 255);
  return Math.round(
    (CesiumMath.clamp(value, -1.0, 1.0) * 0.5 + 0.5) * rangeMaximum
  );
};

/**
 * Converts a SNORM value in the range [0, rangeMaximum] to a scalar in the range [-1.0, 1.0].
 * @param {number} value SNORM value in the range [0, rangeMaximum]
 * @param {number} [rangeMaximum=255] The maximum value in the SNORM range, 255 by default.
 * @returns {number} Scalar in the range [-1.0, 1.0].
 *
 * @see CesiumMath.toSNorm
 */
CesiumMath.fromSNorm = function (value, rangeMaximum) {
  rangeMaximum = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(rangeMaximum, 255);
  return (
    (CesiumMath.clamp(value, 0.0, rangeMaximum) / rangeMaximum) * 2.0 - 1.0
  );
};

/**
 * Converts a scalar value in the range [rangeMinimum, rangeMaximum] to a scalar in the range [0.0, 1.0]
 * @param {number} value The scalar value in the range [rangeMinimum, rangeMaximum]
 * @param {number} rangeMinimum The minimum value in the mapped range.
 * @param {number} rangeMaximum The maximum value in the mapped range.
 * @returns {number} A scalar value, where rangeMinimum maps to 0.0 and rangeMaximum maps to 1.0.
 */
CesiumMath.normalize = function (value, rangeMinimum, rangeMaximum) {
  rangeMaximum = Math.max(rangeMaximum - rangeMinimum, 0.0);
  return rangeMaximum === 0.0
    ? 0.0
    : CesiumMath.clamp((value - rangeMinimum) / rangeMaximum, 0.0, 1.0);
};

/**
 * Returns the hyperbolic sine of a number.
 * The hyperbolic sine of <em>value</em> is defined to be
 * (<em>e<sup>x</sup>&nbsp;-&nbsp;e<sup>-x</sup></em>)/2.0
 * where <i>e</i> is Euler's number, approximately 2.71828183.
 *
 * <p>Special cases:
 *   <ul>
 *     <li>If the argument is NaN, then the result is NaN.</li>
 *
 *     <li>If the argument is infinite, then the result is an infinity
 *     with the same sign as the argument.</li>
 *
 *     <li>If the argument is zero, then the result is a zero with the
 *     same sign as the argument.</li>
 *   </ul>
 *</p>
 *
 * @function
 * @param {number} value The number whose hyperbolic sine is to be returned.
 * @returns {number} The hyperbolic sine of <code>value</code>.
 */
CesiumMath.sinh = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(Math.sinh, function sinh(value) {
  return (Math.exp(value) - Math.exp(-value)) / 2.0;
});

/**
 * Returns the hyperbolic cosine of a number.
 * The hyperbolic cosine of <strong>value</strong> is defined to be
 * (<em>e<sup>x</sup>&nbsp;+&nbsp;e<sup>-x</sup></em>)/2.0
 * where <i>e</i> is Euler's number, approximately 2.71828183.
 *
 * <p>Special cases:
 *   <ul>
 *     <li>If the argument is NaN, then the result is NaN.</li>
 *
 *     <li>If the argument is infinite, then the result is positive infinity.</li>
 *
 *     <li>If the argument is zero, then the result is 1.0.</li>
 *   </ul>
 *</p>
 *
 * @function
 * @param {number} value The number whose hyperbolic cosine is to be returned.
 * @returns {number} The hyperbolic cosine of <code>value</code>.
 */
CesiumMath.cosh = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(Math.cosh, function cosh(value) {
  return (Math.exp(value) + Math.exp(-value)) / 2.0;
});

/**
 * Computes the linear interpolation of two values.
 *
 * @param {number} p The start value to interpolate.
 * @param {number} q The end value to interpolate.
 * @param {number} time The time of interpolation generally in the range <code>[0.0, 1.0]</code>.
 * @returns {number} The linearly interpolated value.
 *
 * @example
 * const n = Cesium.Math.lerp(0.0, 2.0, 0.5); // returns 1.0
 */
CesiumMath.lerp = function (p, q, time) {
  return (1.0 - time) * p + time * q;
};

/**
 * pi
 *
 * @type {number}
 * @constant
 */
CesiumMath.PI = Math.PI;

/**
 * 1/pi
 *
 * @type {number}
 * @constant
 */
CesiumMath.ONE_OVER_PI = 1.0 / Math.PI;

/**
 * pi/2
 *
 * @type {number}
 * @constant
 */
CesiumMath.PI_OVER_TWO = Math.PI / 2.0;

/**
 * pi/3
 *
 * @type {number}
 * @constant
 */
CesiumMath.PI_OVER_THREE = Math.PI / 3.0;

/**
 * pi/4
 *
 * @type {number}
 * @constant
 */
CesiumMath.PI_OVER_FOUR = Math.PI / 4.0;

/**
 * pi/6
 *
 * @type {number}
 * @constant
 */
CesiumMath.PI_OVER_SIX = Math.PI / 6.0;

/**
 * 3pi/2
 *
 * @type {number}
 * @constant
 */
CesiumMath.THREE_PI_OVER_TWO = (3.0 * Math.PI) / 2.0;

/**
 * 2pi
 *
 * @type {number}
 * @constant
 */
CesiumMath.TWO_PI = 2.0 * Math.PI;

/**
 * 1/2pi
 *
 * @type {number}
 * @constant
 */
CesiumMath.ONE_OVER_TWO_PI = 1.0 / (2.0 * Math.PI);

/**
 * The number of radians in a degree.
 *
 * @type {number}
 * @constant
 */
CesiumMath.RADIANS_PER_DEGREE = Math.PI / 180.0;

/**
 * The number of degrees in a radian.
 *
 * @type {number}
 * @constant
 */
CesiumMath.DEGREES_PER_RADIAN = 180.0 / Math.PI;

/**
 * The number of radians in an arc second.
 *
 * @type {number}
 * @constant
 */
CesiumMath.RADIANS_PER_ARCSECOND = CesiumMath.RADIANS_PER_DEGREE / 3600.0;

/**
 * Converts degrees to radians.
 * @param {number} degrees The angle to convert in degrees.
 * @returns {number} The corresponding angle in radians.
 */
CesiumMath.toRadians = function (degrees) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(degrees)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("degrees is required.");
  }
  //>>includeEnd('debug');
  return degrees * CesiumMath.RADIANS_PER_DEGREE;
};

/**
 * Converts radians to degrees.
 * @param {number} radians The angle to convert in radians.
 * @returns {number} The corresponding angle in degrees.
 */
CesiumMath.toDegrees = function (radians) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(radians)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("radians is required.");
  }
  //>>includeEnd('debug');
  return radians * CesiumMath.DEGREES_PER_RADIAN;
};

/**
 * Converts a longitude value, in radians, to the range [<code>-Math.PI</code>, <code>Math.PI</code>).
 *
 * @param {number} angle The longitude value, in radians, to convert to the range [<code>-Math.PI</code>, <code>Math.PI</code>).
 * @returns {number} The equivalent longitude value in the range [<code>-Math.PI</code>, <code>Math.PI</code>).
 *
 * @example
 * // Convert 270 degrees to -90 degrees longitude
 * const longitude = Cesium.Math.convertLongitudeRange(Cesium.Math.toRadians(270.0));
 */
CesiumMath.convertLongitudeRange = function (angle) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(angle)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("angle is required.");
  }
  //>>includeEnd('debug');
  const twoPi = CesiumMath.TWO_PI;

  const simplified = angle - Math.floor(angle / twoPi) * twoPi;

  if (simplified < -Math.PI) {
    return simplified + twoPi;
  }
  if (simplified >= Math.PI) {
    return simplified - twoPi;
  }

  return simplified;
};

/**
 * Convenience function that clamps a latitude value, in radians, to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
 * Useful for sanitizing data before use in objects requiring correct range.
 *
 * @param {number} angle The latitude value, in radians, to clamp to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
 * @returns {number} The latitude value clamped to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
 *
 * @example
 * // Clamp 108 degrees latitude to 90 degrees latitude
 * const latitude = Cesium.Math.clampToLatitudeRange(Cesium.Math.toRadians(108.0));
 */
CesiumMath.clampToLatitudeRange = function (angle) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(angle)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("angle is required.");
  }
  //>>includeEnd('debug');

  return CesiumMath.clamp(
    angle,
    -1 * CesiumMath.PI_OVER_TWO,
    CesiumMath.PI_OVER_TWO
  );
};

/**
 * Produces an angle in the range -Pi <= angle <= Pi which is equivalent to the provided angle.
 *
 * @param {number} angle in radians
 * @returns {number} The angle in the range [<code>-CesiumMath.PI</code>, <code>CesiumMath.PI</code>].
 */
CesiumMath.negativePiToPi = function (angle) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(angle)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("angle is required.");
  }
  //>>includeEnd('debug');
  if (angle >= -CesiumMath.PI && angle <= CesiumMath.PI) {
    // Early exit if the input is already inside the range. This avoids
    // unnecessary math which could introduce floating point error.
    return angle;
  }
  return CesiumMath.zeroToTwoPi(angle + CesiumMath.PI) - CesiumMath.PI;
};

/**
 * Produces an angle in the range 0 <= angle <= 2Pi which is equivalent to the provided angle.
 *
 * @param {number} angle in radians
 * @returns {number} The angle in the range [0, <code>CesiumMath.TWO_PI</code>].
 */
CesiumMath.zeroToTwoPi = function (angle) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(angle)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("angle is required.");
  }
  //>>includeEnd('debug');
  if (angle >= 0 && angle <= CesiumMath.TWO_PI) {
    // Early exit if the input is already inside the range. This avoids
    // unnecessary math which could introduce floating point error.
    return angle;
  }
  const mod = CesiumMath.mod(angle, CesiumMath.TWO_PI);
  if (
    Math.abs(mod) < CesiumMath.EPSILON14 &&
    Math.abs(angle) > CesiumMath.EPSILON14
  ) {
    return CesiumMath.TWO_PI;
  }
  return mod;
};

/**
 * The modulo operation that also works for negative dividends.
 *
 * @param {number} m The dividend.
 * @param {number} n The divisor.
 * @returns {number} The remainder.
 */
CesiumMath.mod = function (m, n) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(m)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("m is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(n)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("n is required.");
  }
  if (n === 0.0) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("divisor cannot be 0.");
  }
  //>>includeEnd('debug');
  if (CesiumMath.sign(m) === CesiumMath.sign(n) && Math.abs(m) < Math.abs(n)) {
    // Early exit if the input does not need to be modded. This avoids
    // unnecessary math which could introduce floating point error.
    return m;
  }

  return ((m % n) + n) % n;
};

/**
 * Determines if two values are equal using an absolute or relative tolerance test. This is useful
 * to avoid problems due to roundoff error when comparing floating-point values directly. The values are
 * first compared using an absolute tolerance test. If that fails, a relative tolerance test is performed.
 * Use this test if you are unsure of the magnitudes of left and right.
 *
 * @param {number} left The first value to compare.
 * @param {number} right The other value to compare.
 * @param {number} [relativeEpsilon=0] The maximum inclusive delta between <code>left</code> and <code>right</code> for the relative tolerance test.
 * @param {number} [absoluteEpsilon=relativeEpsilon] The maximum inclusive delta between <code>left</code> and <code>right</code> for the absolute tolerance test.
 * @returns {boolean} <code>true</code> if the values are equal within the epsilon; otherwise, <code>false</code>.
 *
 * @example
 * const a = Cesium.Math.equalsEpsilon(0.0, 0.01, Cesium.Math.EPSILON2); // true
 * const b = Cesium.Math.equalsEpsilon(0.0, 0.1, Cesium.Math.EPSILON2);  // false
 * const c = Cesium.Math.equalsEpsilon(3699175.1634344, 3699175.2, Cesium.Math.EPSILON7); // true
 * const d = Cesium.Math.equalsEpsilon(3699175.1634344, 3699175.2, Cesium.Math.EPSILON9); // false
 */
CesiumMath.equalsEpsilon = function (
  left,
  right,
  relativeEpsilon,
  absoluteEpsilon
) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("left is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("right is required.");
  }
  //>>includeEnd('debug');

  relativeEpsilon = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(relativeEpsilon, 0.0);
  absoluteEpsilon = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(absoluteEpsilon, relativeEpsilon);
  const absDiff = Math.abs(left - right);
  return (
    absDiff <= absoluteEpsilon ||
    absDiff <= relativeEpsilon * Math.max(Math.abs(left), Math.abs(right))
  );
};

/**
 * Determines if the left value is less than the right value. If the two values are within
 * <code>absoluteEpsilon</code> of each other, they are considered equal and this function returns false.
 *
 * @param {number} left The first number to compare.
 * @param {number} right The second number to compare.
 * @param {number} absoluteEpsilon The absolute epsilon to use in comparison.
 * @returns {boolean} <code>true</code> if <code>left</code> is less than <code>right</code> by more than
 *          <code>absoluteEpsilon<code>. <code>false</code> if <code>left</code> is greater or if the two
 *          values are nearly equal.
 */
CesiumMath.lessThan = function (left, right, absoluteEpsilon) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("first is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("second is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(absoluteEpsilon)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("absoluteEpsilon is required.");
  }
  //>>includeEnd('debug');
  return left - right < -absoluteEpsilon;
};

/**
 * Determines if the left value is less than or equal to the right value. If the two values are within
 * <code>absoluteEpsilon</code> of each other, they are considered equal and this function returns true.
 *
 * @param {number} left The first number to compare.
 * @param {number} right The second number to compare.
 * @param {number} absoluteEpsilon The absolute epsilon to use in comparison.
 * @returns {boolean} <code>true</code> if <code>left</code> is less than <code>right</code> or if the
 *          the values are nearly equal.
 */
CesiumMath.lessThanOrEquals = function (left, right, absoluteEpsilon) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("first is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("second is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(absoluteEpsilon)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("absoluteEpsilon is required.");
  }
  //>>includeEnd('debug');
  return left - right < absoluteEpsilon;
};

/**
 * Determines if the left value is greater the right value. If the two values are within
 * <code>absoluteEpsilon</code> of each other, they are considered equal and this function returns false.
 *
 * @param {number} left The first number to compare.
 * @param {number} right The second number to compare.
 * @param {number} absoluteEpsilon The absolute epsilon to use in comparison.
 * @returns {boolean} <code>true</code> if <code>left</code> is greater than <code>right</code> by more than
 *          <code>absoluteEpsilon<code>. <code>false</code> if <code>left</code> is less or if the two
 *          values are nearly equal.
 */
CesiumMath.greaterThan = function (left, right, absoluteEpsilon) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("first is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("second is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(absoluteEpsilon)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("absoluteEpsilon is required.");
  }
  //>>includeEnd('debug');
  return left - right > absoluteEpsilon;
};

/**
 * Determines if the left value is greater than or equal to the right value. If the two values are within
 * <code>absoluteEpsilon</code> of each other, they are considered equal and this function returns true.
 *
 * @param {number} left The first number to compare.
 * @param {number} right The second number to compare.
 * @param {number} absoluteEpsilon The absolute epsilon to use in comparison.
 * @returns {boolean} <code>true</code> if <code>left</code> is greater than <code>right</code> or if the
 *          the values are nearly equal.
 */
CesiumMath.greaterThanOrEquals = function (left, right, absoluteEpsilon) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("first is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("second is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(absoluteEpsilon)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("absoluteEpsilon is required.");
  }
  //>>includeEnd('debug');
  return left - right > -absoluteEpsilon;
};

const factorials = [1];

/**
 * Computes the factorial of the provided number.
 *
 * @param {number} n The number whose factorial is to be computed.
 * @returns {number} The factorial of the provided number or undefined if the number is less than 0.
 *
 * @exception {DeveloperError} A number greater than or equal to 0 is required.
 *
 *
 * @example
 * //Compute 7!, which is equal to 5040
 * const computedFactorial = Cesium.Math.factorial(7);
 *
 * @see {@link http://en.wikipedia.org/wiki/Factorial|Factorial on Wikipedia}
 */
CesiumMath.factorial = function (n) {
  //>>includeStart('debug', pragmas.debug);
  if (typeof n !== "number" || n < 0) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"](
      "A number greater than or equal to 0 is required."
    );
  }
  //>>includeEnd('debug');

  const length = factorials.length;
  if (n >= length) {
    let sum = factorials[length - 1];
    for (let i = length; i <= n; i++) {
      const next = sum * i;
      factorials.push(next);
      sum = next;
    }
  }
  return factorials[n];
};

/**
 * Increments a number with a wrapping to a minimum value if the number exceeds the maximum value.
 *
 * @param {number} [n] The number to be incremented.
 * @param {number} [maximumValue] The maximum incremented value before rolling over to the minimum value.
 * @param {number} [minimumValue=0.0] The number reset to after the maximum value has been exceeded.
 * @returns {number} The incremented number.
 *
 * @exception {DeveloperError} Maximum value must be greater than minimum value.
 *
 * @example
 * const n = Cesium.Math.incrementWrap(5, 10, 0); // returns 6
 * const m = Cesium.Math.incrementWrap(10, 10, 0); // returns 0
 */
CesiumMath.incrementWrap = function (n, maximumValue, minimumValue) {
  minimumValue = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(minimumValue, 0.0);

  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(n)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("n is required.");
  }
  if (maximumValue <= minimumValue) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("maximumValue must be greater than minimumValue.");
  }
  //>>includeEnd('debug');

  ++n;
  if (n > maximumValue) {
    n = minimumValue;
  }
  return n;
};

/**
 * Determines if a non-negative integer is a power of two.
 * The maximum allowed input is (2^32)-1 due to 32-bit bitwise operator limitation in Javascript.
 *
 * @param {number} n The integer to test in the range [0, (2^32)-1].
 * @returns {boolean} <code>true</code> if the number if a power of two; otherwise, <code>false</code>.
 *
 * @exception {DeveloperError} A number between 0 and (2^32)-1 is required.
 *
 * @example
 * const t = Cesium.Math.isPowerOfTwo(16); // true
 * const f = Cesium.Math.isPowerOfTwo(20); // false
 */
CesiumMath.isPowerOfTwo = function (n) {
  //>>includeStart('debug', pragmas.debug);
  if (typeof n !== "number" || n < 0 || n > 4294967295) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("A number between 0 and (2^32)-1 is required.");
  }
  //>>includeEnd('debug');

  return n !== 0 && (n & (n - 1)) === 0;
};

/**
 * Computes the next power-of-two integer greater than or equal to the provided non-negative integer.
 * The maximum allowed input is 2^31 due to 32-bit bitwise operator limitation in Javascript.
 *
 * @param {number} n The integer to test in the range [0, 2^31].
 * @returns {number} The next power-of-two integer.
 *
 * @exception {DeveloperError} A number between 0 and 2^31 is required.
 *
 * @example
 * const n = Cesium.Math.nextPowerOfTwo(29); // 32
 * const m = Cesium.Math.nextPowerOfTwo(32); // 32
 */
CesiumMath.nextPowerOfTwo = function (n) {
  //>>includeStart('debug', pragmas.debug);
  if (typeof n !== "number" || n < 0 || n > 2147483648) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("A number between 0 and 2^31 is required.");
  }
  //>>includeEnd('debug');

  // From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  ++n;

  return n;
};

/**
 * Computes the previous power-of-two integer less than or equal to the provided non-negative integer.
 * The maximum allowed input is (2^32)-1 due to 32-bit bitwise operator limitation in Javascript.
 *
 * @param {number} n The integer to test in the range [0, (2^32)-1].
 * @returns {number} The previous power-of-two integer.
 *
 * @exception {DeveloperError} A number between 0 and (2^32)-1 is required.
 *
 * @example
 * const n = Cesium.Math.previousPowerOfTwo(29); // 16
 * const m = Cesium.Math.previousPowerOfTwo(32); // 32
 */
CesiumMath.previousPowerOfTwo = function (n) {
  //>>includeStart('debug', pragmas.debug);
  if (typeof n !== "number" || n < 0 || n > 4294967295) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("A number between 0 and (2^32)-1 is required.");
  }
  //>>includeEnd('debug');

  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n |= n >> 32;

  // The previous bitwise operations implicitly convert to signed 32-bit. Use `>>>` to convert to unsigned
  n = (n >>> 0) - (n >>> 1);

  return n;
};

/**
 * Constraint a value to lie between two values.
 *
 * @param {number} value The value to clamp.
 * @param {number} min The minimum value.
 * @param {number} max The maximum value.
 * @returns {number} The clamped value such that min <= result <= max.
 */
CesiumMath.clamp = function (value, min, max) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("value", value);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("min", min);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("max", max);
  //>>includeEnd('debug');

  return value < min ? min : value > max ? max : value;
};

let randomNumberGenerator = new mersenne_twister__WEBPACK_IMPORTED_MODULE_0__();

/**
 * Sets the seed used by the random number generator
 * in {@link CesiumMath#nextRandomNumber}.
 *
 * @param {number} seed An integer used as the seed.
 */
CesiumMath.setRandomNumberSeed = function (seed) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(seed)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("seed is required.");
  }
  //>>includeEnd('debug');

  randomNumberGenerator = new mersenne_twister__WEBPACK_IMPORTED_MODULE_0__(seed);
};

/**
 * Generates a random floating point number in the range of [0.0, 1.0)
 * using a Mersenne twister.
 *
 * @returns {number} A random number in the range of [0.0, 1.0).
 *
 * @see CesiumMath.setRandomNumberSeed
 * @see {@link http://en.wikipedia.org/wiki/Mersenne_twister|Mersenne twister on Wikipedia}
 */
CesiumMath.nextRandomNumber = function () {
  return randomNumberGenerator.random();
};

/**
 * Generates a random number between two numbers.
 *
 * @param {number} min The minimum value.
 * @param {number} max The maximum value.
 * @returns {number} A random number between the min and max.
 */
CesiumMath.randomBetween = function (min, max) {
  return CesiumMath.nextRandomNumber() * (max - min) + min;
};

/**
 * Computes <code>Math.acos(value)</code>, but first clamps <code>value</code> to the range [-1.0, 1.0]
 * so that the function will never return NaN.
 *
 * @param {number} value The value for which to compute acos.
 * @returns {number} The acos of the value if the value is in the range [-1.0, 1.0], or the acos of -1.0 or 1.0,
 *          whichever is closer, if the value is outside the range.
 */
CesiumMath.acosClamped = function (value) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(value)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("value is required.");
  }
  //>>includeEnd('debug');
  return Math.acos(CesiumMath.clamp(value, -1.0, 1.0));
};

/**
 * Computes <code>Math.asin(value)</code>, but first clamps <code>value</code> to the range [-1.0, 1.0]
 * so that the function will never return NaN.
 *
 * @param {number} value The value for which to compute asin.
 * @returns {number} The asin of the value if the value is in the range [-1.0, 1.0], or the asin of -1.0 or 1.0,
 *          whichever is closer, if the value is outside the range.
 */
CesiumMath.asinClamped = function (value) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(value)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("value is required.");
  }
  //>>includeEnd('debug');
  return Math.asin(CesiumMath.clamp(value, -1.0, 1.0));
};

/**
 * Finds the chord length between two points given the circle's radius and the angle between the points.
 *
 * @param {number} angle The angle between the two points.
 * @param {number} radius The radius of the circle.
 * @returns {number} The chord length.
 */
CesiumMath.chordLength = function (angle, radius) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(angle)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("angle is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(radius)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("radius is required.");
  }
  //>>includeEnd('debug');
  return 2.0 * radius * Math.sin(angle * 0.5);
};

/**
 * Finds the logarithm of a number to a base.
 *
 * @param {number} number The number.
 * @param {number} base The base.
 * @returns {number} The result.
 */
CesiumMath.logBase = function (number, base) {
  //>>includeStart('debug', pragmas.debug);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(number)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("number is required.");
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(base)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("base is required.");
  }
  //>>includeEnd('debug');
  return Math.log(number) / Math.log(base);
};

/**
 * Finds the cube root of a number.
 * Returns NaN if <code>number</code> is not provided.
 *
 * @function
 * @param {number} [number] The number.
 * @returns {number} The result.
 */
CesiumMath.cbrt = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(Math.cbrt, function cbrt(number) {
  const result = Math.pow(Math.abs(number), 1.0 / 3.0);
  return number < 0.0 ? -result : result;
});

/**
 * Finds the base 2 logarithm of a number.
 *
 * @function
 * @param {number} number The number.
 * @returns {number} The result.
 */
CesiumMath.log2 = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_1__["default"])(Math.log2, function log2(number) {
  return Math.log(number) * Math.LOG2E;
});

/**
 * @private
 */
CesiumMath.fog = function (distanceToCamera, density) {
  const scalar = distanceToCamera * density;
  return 1.0 - Math.exp(-(scalar * scalar));
};

/**
 * Computes a fast approximation of Atan for input in the range [-1, 1].
 *
 * Based on Michal Drobot's approximation from ShaderFastLibs,
 * which in turn is based on "Efficient approximations for the arctangent function,"
 * Rajan, S. Sichun Wang Inkol, R. Joyal, A., May 2006.
 * Adapted from ShaderFastLibs under MIT License.
 *
 * @param {number} x An input number in the range [-1, 1]
 * @returns {number} An approximation of atan(x)
 */
CesiumMath.fastApproximateAtan = function (x) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("x", x);
  //>>includeEnd('debug');

  return x * (-0.1784 * Math.abs(x) - 0.0663 * x * x + 1.0301);
};

/**
 * Computes a fast approximation of Atan2(x, y) for arbitrary input scalars.
 *
 * Range reduction math based on nvidia's cg reference implementation: http://developer.download.nvidia.com/cg/atan2.html
 *
 * @param {number} x An input number that isn't zero if y is zero.
 * @param {number} y An input number that isn't zero if x is zero.
 * @returns {number} An approximation of atan2(x, y)
 */
CesiumMath.fastApproximateAtan2 = function (x, y) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("x", x);
  _Check_js__WEBPACK_IMPORTED_MODULE_4__["default"].typeOf.number("y", y);
  //>>includeEnd('debug');

  // atan approximations are usually only reliable over [-1, 1]
  // So reduce the range by flipping whether x or y is on top based on which is bigger.
  let opposite;
  let t = Math.abs(x); // t used as swap and atan result.
  opposite = Math.abs(y);
  const adjacent = Math.max(t, opposite);
  opposite = Math.min(t, opposite);

  const oppositeOverAdjacent = opposite / adjacent;
  //>>includeStart('debug', pragmas.debug);
  if (isNaN(oppositeOverAdjacent)) {
    throw new _DeveloperError_js__WEBPACK_IMPORTED_MODULE_3__["default"]("either x or y must be nonzero");
  }
  //>>includeEnd('debug');
  t = CesiumMath.fastApproximateAtan(oppositeOverAdjacent);

  // Undo range reduction
  t = Math.abs(y) > Math.abs(x) ? CesiumMath.PI_OVER_TWO - t : t;
  t = x < 0.0 ? CesiumMath.PI - t : t;
  t = y < 0.0 ? -t : t;
  return t;
};
/* harmony default export */ __webpack_exports__["default"] = (CesiumMath);


/***/ }),
/* 8 */
/***/ (function(module) {

/*
  https://github.com/banksean wrapped Makoto Matsumoto and Takuji Nishimura's code in a namespace
  so it's better encapsulated. Now you can have multiple random number generators
  and they won't stomp all over eachother's state.

  If you want to use this as a substitute for Math.random(), use the random()
  method like so:

  var m = new MersenneTwister();
  var randomNumber = m.random();

  You can also call the other genrand_{foo}() methods on the instance.

  If you want to use a specific seed in order to get a repeatable random
  sequence, pass an integer into the constructor:

  var m = new MersenneTwister(123);

  and that will always produce the same random sequence.

  Sean McCullough (banksean@gmail.com)
*/

/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_seed(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

var MersenneTwister = function(seed) {
	if (seed == undefined) {
		seed = new Date().getTime();
	}

	/* Period parameters */
	this.N = 624;
	this.M = 397;
	this.MATRIX_A = 0x9908b0df;   /* constant vector a */
	this.UPPER_MASK = 0x80000000; /* most significant w-r bits */
	this.LOWER_MASK = 0x7fffffff; /* least significant r bits */

	this.mt = new Array(this.N); /* the array for the state vector */
	this.mti=this.N+1; /* mti==N+1 means mt[N] is not initialized */

	if (seed.constructor == Array) {
		this.init_by_array(seed, seed.length);
	}
	else {
		this.init_seed(seed);
	}
}

/* initializes mt[N] with a seed */
/* origin name init_genrand */
MersenneTwister.prototype.init_seed = function(s) {
	this.mt[0] = s >>> 0;
	for (this.mti=1; this.mti<this.N; this.mti++) {
		var s = this.mt[this.mti-1] ^ (this.mt[this.mti-1] >>> 30);
		this.mt[this.mti] = (((((s & 0xffff0000) >>> 16) * 1812433253) << 16) + (s & 0x0000ffff) * 1812433253)
		+ this.mti;
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		this.mt[this.mti] >>>= 0;
		/* for >32 bit machines */
	}
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
MersenneTwister.prototype.init_by_array = function(init_key, key_length) {
	var i, j, k;
	this.init_seed(19650218);
	i=1; j=0;
	k = (this.N>key_length ? this.N : key_length);
	for (; k; k--) {
		var s = this.mt[i-1] ^ (this.mt[i-1] >>> 30)
		this.mt[i] = (this.mt[i] ^ (((((s & 0xffff0000) >>> 16) * 1664525) << 16) + ((s & 0x0000ffff) * 1664525)))
		+ init_key[j] + j; /* non linear */
		this.mt[i] >>>= 0; /* for WORDSIZE > 32 machines */
		i++; j++;
		if (i>=this.N) { this.mt[0] = this.mt[this.N-1]; i=1; }
		if (j>=key_length) j=0;
	}
	for (k=this.N-1; k; k--) {
		var s = this.mt[i-1] ^ (this.mt[i-1] >>> 30);
		this.mt[i] = (this.mt[i] ^ (((((s & 0xffff0000) >>> 16) * 1566083941) << 16) + (s & 0x0000ffff) * 1566083941))
		- i; /* non linear */
		this.mt[i] >>>= 0; /* for WORDSIZE > 32 machines */
		i++;
		if (i>=this.N) { this.mt[0] = this.mt[this.N-1]; i=1; }
	}

	this.mt[0] = 0x80000000; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
/* origin name genrand_int32 */
MersenneTwister.prototype.random_int = function() {
	var y;
	var mag01 = new Array(0x0, this.MATRIX_A);
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (this.mti >= this.N) { /* generate N words at one time */
		var kk;

		if (this.mti == this.N+1)  /* if init_seed() has not been called, */
			this.init_seed(5489);  /* a default initial seed is used */

		for (kk=0;kk<this.N-this.M;kk++) {
			y = (this.mt[kk]&this.UPPER_MASK)|(this.mt[kk+1]&this.LOWER_MASK);
			this.mt[kk] = this.mt[kk+this.M] ^ (y >>> 1) ^ mag01[y & 0x1];
		}
		for (;kk<this.N-1;kk++) {
			y = (this.mt[kk]&this.UPPER_MASK)|(this.mt[kk+1]&this.LOWER_MASK);
			this.mt[kk] = this.mt[kk+(this.M-this.N)] ^ (y >>> 1) ^ mag01[y & 0x1];
		}
		y = (this.mt[this.N-1]&this.UPPER_MASK)|(this.mt[0]&this.LOWER_MASK);
		this.mt[this.N-1] = this.mt[this.M-1] ^ (y >>> 1) ^ mag01[y & 0x1];

		this.mti = 0;
	}

	y = this.mt[this.mti++];

	/* Tempering */
	y ^= (y >>> 11);
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	y ^= (y >>> 18);

	return y >>> 0;
}

/* generates a random number on [0,0x7fffffff]-interval */
/* origin name genrand_int31 */
MersenneTwister.prototype.random_int31 = function() {
	return (this.random_int()>>>1);
}

/* generates a random number on [0,1]-real-interval */
/* origin name genrand_real1 */
MersenneTwister.prototype.random_incl = function() {
	return this.random_int()*(1.0/4294967295.0);
	/* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
MersenneTwister.prototype.random = function() {
	return this.random_int()*(1.0/4294967296.0);
	/* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
/* origin name genrand_real3 */
MersenneTwister.prototype.random_excl = function() {
	return (this.random_int() + 0.5)*(1.0/4294967296.0);
	/* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
/* origin name genrand_res53 */
MersenneTwister.prototype.random_long = function() {
	var a=this.random_int()>>>5, b=this.random_int()>>>6;
	return(a*67108864.0+b)*(1.0/9007199254740992.0);
}

/* These real versions are due to Isaku Wada, 2002/01/09 added */

module.exports = MersenneTwister;


/***/ })
/******/ 	]);
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	/* webpack/runtime/make namespace object */
/******/ 	!function() {
/******/ 		// define __esModule on exports
/******/ 		__webpack_require__.r = function(exports) {
/******/ 			if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 				Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 			}
/******/ 			Object.defineProperty(exports, '__esModule', { value: true });
/******/ 		};
/******/ 	}();
/******/ 	
/************************************************************************/
var __webpack_exports__ = {};
// This entry need to be wrapped in an IIFE because it need to be in strict mode.
!function() {
"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _Check_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(1);
/* harmony import */ var _defaultValue_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(4);
/* harmony import */ var _defined_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(2);
/* harmony import */ var _FeatureDetection_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(5);
/* harmony import */ var _Math_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(7);






function hue2rgb(m1, m2, h) {
  if (h < 0) {
    h += 1;
  }
  if (h > 1) {
    h -= 1;
  }
  if (h * 6 < 1) {
    return m1 + (m2 - m1) * 6 * h;
  }
  if (h * 2 < 1) {
    return m2;
  }
  if (h * 3 < 2) {
    return m1 + (m2 - m1) * (2 / 3 - h) * 6;
  }
  return m1;
}

/**
 * A color, specified using red, green, blue, and alpha values,
 * which range from <code>0</code> (no intensity) to <code>1.0</code> (full intensity).
 * @param {number} [red=1.0] The red component.
 * @param {number} [green=1.0] The green component.
 * @param {number} [blue=1.0] The blue component.
 * @param {number} [alpha=1.0] The alpha component.
 *
 * @constructor
 * @alias Color
 *
 * @see Packable
 */
function Color(red, green, blue, alpha) {
  /**
   * The red component.
   * @type {number}
   * @default 1.0
   */
  this.red = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(red, 1.0);
  /**
   * The green component.
   * @type {number}
   * @default 1.0
   */
  this.green = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(green, 1.0);
  /**
   * The blue component.
   * @type {number}
   * @default 1.0
   */
  this.blue = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(blue, 1.0);
  /**
   * The alpha component.
   * @type {number}
   * @default 1.0
   */
  this.alpha = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(alpha, 1.0);
}

/**
 * Creates a Color instance from a {@link Cartesian4}. <code>x</code>, <code>y</code>, <code>z</code>,
 * and <code>w</code> map to <code>red</code>, <code>green</code>, <code>blue</code>, and <code>alpha</code>, respectively.
 *
 * @param {Cartesian4} cartesian The source cartesian.
 * @param {Color} [result] The object onto which to store the result.
 * @returns {Color} The modified result parameter or a new Color instance if one was not provided.
 */
Color.fromCartesian4 = function (cartesian, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("cartesian", cartesian);
  //>>includeEnd('debug');

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(cartesian.x, cartesian.y, cartesian.z, cartesian.w);
  }

  result.red = cartesian.x;
  result.green = cartesian.y;
  result.blue = cartesian.z;
  result.alpha = cartesian.w;
  return result;
};

/**
 * Creates a new Color specified using red, green, blue, and alpha values
 * that are in the range of 0 to 255, converting them internally to a range of 0.0 to 1.0.
 *
 * @param {number} [red=255] The red component.
 * @param {number} [green=255] The green component.
 * @param {number} [blue=255] The blue component.
 * @param {number} [alpha=255] The alpha component.
 * @param {Color} [result] The object onto which to store the result.
 * @returns {Color} The modified result parameter or a new Color instance if one was not provided.
 */
Color.fromBytes = function (red, green, blue, alpha, result) {
  red = Color.byteToFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(red, 255.0));
  green = Color.byteToFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(green, 255.0));
  blue = Color.byteToFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(blue, 255.0));
  alpha = Color.byteToFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(alpha, 255.0));

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(red, green, blue, alpha);
  }

  result.red = red;
  result.green = green;
  result.blue = blue;
  result.alpha = alpha;
  return result;
};

/**
 * Creates a new Color that has the same red, green, and blue components
 * of the specified color, but with the specified alpha value.
 *
 * @param {Color} color The base color
 * @param {number} alpha The new alpha component.
 * @param {Color} [result] The object onto which to store the result.
 * @returns {Color} The modified result parameter or a new Color instance if one was not provided.
 *
 * @example const translucentRed = Cesium.Color.fromAlpha(Cesium.Color.RED, 0.9);
 */
Color.fromAlpha = function (color, alpha, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("color", color);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("alpha", alpha);
  //>>includeEnd('debug');

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(color.red, color.green, color.blue, alpha);
  }

  result.red = color.red;
  result.green = color.green;
  result.blue = color.blue;
  result.alpha = alpha;
  return result;
};

let scratchArrayBuffer;
let scratchUint32Array;
let scratchUint8Array;
if (_FeatureDetection_js__WEBPACK_IMPORTED_MODULE_3__["default"].supportsTypedArrays()) {
  scratchArrayBuffer = new ArrayBuffer(4);
  scratchUint32Array = new Uint32Array(scratchArrayBuffer);
  scratchUint8Array = new Uint8Array(scratchArrayBuffer);
}

/**
 * Creates a new Color from a single numeric unsigned 32-bit RGBA value, using the endianness
 * of the system.
 *
 * @param {number} rgba A single numeric unsigned 32-bit RGBA value.
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The color object.
 *
 * @example
 * const color = Cesium.Color.fromRgba(0x67ADDFFF);
 *
 * @see Color#toRgba
 */
Color.fromRgba = function (rgba, result) {
  // scratchUint32Array and scratchUint8Array share an underlying array buffer
  scratchUint32Array[0] = rgba;
  return Color.fromBytes(
    scratchUint8Array[0],
    scratchUint8Array[1],
    scratchUint8Array[2],
    scratchUint8Array[3],
    result
  );
};

/**
 * Creates a Color instance from hue, saturation, and lightness.
 *
 * @param {number} [hue=0] The hue angle 0...1
 * @param {number} [saturation=0] The saturation value 0...1
 * @param {number} [lightness=0] The lightness value 0...1
 * @param {number} [alpha=1.0] The alpha component 0...1
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The color object.
 *
 * @see {@link http://www.w3.org/TR/css3-color/#hsl-color|CSS color values}
 */
Color.fromHsl = function (hue, saturation, lightness, alpha, result) {
  hue = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(hue, 0.0) % 1.0;
  saturation = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(saturation, 0.0);
  lightness = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(lightness, 0.0);
  alpha = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(alpha, 1.0);

  let red = lightness;
  let green = lightness;
  let blue = lightness;

  if (saturation !== 0) {
    let m2;
    if (lightness < 0.5) {
      m2 = lightness * (1 + saturation);
    } else {
      m2 = lightness + saturation - lightness * saturation;
    }

    const m1 = 2.0 * lightness - m2;
    red = hue2rgb(m1, m2, hue + 1 / 3);
    green = hue2rgb(m1, m2, hue);
    blue = hue2rgb(m1, m2, hue - 1 / 3);
  }

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(red, green, blue, alpha);
  }

  result.red = red;
  result.green = green;
  result.blue = blue;
  result.alpha = alpha;
  return result;
};

/**
 * Creates a random color using the provided options. For reproducible random colors, you should
 * call {@link CesiumMath#setRandomNumberSeed} once at the beginning of your application.
 *
 * @param {object} [options] Object with the following properties:
 * @param {number} [options.red] If specified, the red component to use instead of a randomized value.
 * @param {number} [options.minimumRed=0.0] The maximum red value to generate if none was specified.
 * @param {number} [options.maximumRed=1.0] The minimum red value to generate if none was specified.
 * @param {number} [options.green] If specified, the green component to use instead of a randomized value.
 * @param {number} [options.minimumGreen=0.0] The maximum green value to generate if none was specified.
 * @param {number} [options.maximumGreen=1.0] The minimum green value to generate if none was specified.
 * @param {number} [options.blue] If specified, the blue component to use instead of a randomized value.
 * @param {number} [options.minimumBlue=0.0] The maximum blue value to generate if none was specified.
 * @param {number} [options.maximumBlue=1.0] The minimum blue value to generate if none was specified.
 * @param {number} [options.alpha] If specified, the alpha component to use instead of a randomized value.
 * @param {number} [options.minimumAlpha=0.0] The maximum alpha value to generate if none was specified.
 * @param {number} [options.maximumAlpha=1.0] The minimum alpha value to generate if none was specified.
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The modified result parameter or a new instance if result was undefined.
 *
 * @exception {DeveloperError} minimumRed must be less than or equal to maximumRed.
 * @exception {DeveloperError} minimumGreen must be less than or equal to maximumGreen.
 * @exception {DeveloperError} minimumBlue must be less than or equal to maximumBlue.
 * @exception {DeveloperError} minimumAlpha must be less than or equal to maximumAlpha.
 *
 * @example
 * //Create a completely random color
 * const color = Cesium.Color.fromRandom();
 *
 * //Create a random shade of yellow.
 * const color1 = Cesium.Color.fromRandom({
 *     red : 1.0,
 *     green : 1.0,
 *     alpha : 1.0
 * });
 *
 * //Create a random bright color.
 * const color2 = Cesium.Color.fromRandom({
 *     minimumRed : 0.75,
 *     minimumGreen : 0.75,
 *     minimumBlue : 0.75,
 *     alpha : 1.0
 * });
 */
Color.fromRandom = function (options, result) {
  options = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options, _defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"].EMPTY_OBJECT);

  let red = options.red;
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(red)) {
    const minimumRed = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.minimumRed, 0);
    const maximumRed = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.maximumRed, 1.0);

    //>>includeStart('debug', pragmas.debug);
    _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.lessThanOrEquals("minimumRed", minimumRed, maximumRed);
    //>>includeEnd('debug');

    red =
      minimumRed + _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].nextRandomNumber() * (maximumRed - minimumRed);
  }

  let green = options.green;
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(green)) {
    const minimumGreen = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.minimumGreen, 0);
    const maximumGreen = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.maximumGreen, 1.0);

    //>>includeStart('debug', pragmas.debug);
    _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.lessThanOrEquals(
      "minimumGreen",
      minimumGreen,
      maximumGreen
    );
    //>>includeEnd('debug');
    green =
      minimumGreen +
      _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].nextRandomNumber() * (maximumGreen - minimumGreen);
  }

  let blue = options.blue;
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(blue)) {
    const minimumBlue = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.minimumBlue, 0);
    const maximumBlue = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.maximumBlue, 1.0);

    //>>includeStart('debug', pragmas.debug);
    _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.lessThanOrEquals(
      "minimumBlue",
      minimumBlue,
      maximumBlue
    );
    //>>includeEnd('debug');

    blue =
      minimumBlue + _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].nextRandomNumber() * (maximumBlue - minimumBlue);
  }

  let alpha = options.alpha;
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(alpha)) {
    const minimumAlpha = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.minimumAlpha, 0);
    const maximumAlpha = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(options.maximumAlpha, 1.0);

    //>>includeStart('debug', pragmas.debug);
    _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.lessThanOrEquals(
      "minumumAlpha",
      minimumAlpha,
      maximumAlpha
    );
    //>>includeEnd('debug');

    alpha =
      minimumAlpha +
      _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].nextRandomNumber() * (maximumAlpha - minimumAlpha);
  }

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(red, green, blue, alpha);
  }

  result.red = red;
  result.green = green;
  result.blue = blue;
  result.alpha = alpha;
  return result;
};

//#rgba
const rgbaMatcher = /^#([0-9a-f])([0-9a-f])([0-9a-f])([0-9a-f])?$/i;
//#rrggbbaa
const rrggbbaaMatcher = /^#([0-9a-f]{2})([0-9a-f]{2})([0-9a-f]{2})([0-9a-f]{2})?$/i;
//rgb(), rgba(), or rgb%()
const rgbParenthesesMatcher = /^rgba?\s*\(\s*([0-9.]+%?)\s*[,\s]+\s*([0-9.]+%?)\s*[,\s]+\s*([0-9.]+%?)(?:\s*[,\s/]+\s*([0-9.]+))?\s*\)$/i;
//hsl() or hsla()
const hslParenthesesMatcher = /^hsla?\s*\(\s*([0-9.]+)\s*[,\s]+\s*([0-9.]+%)\s*[,\s]+\s*([0-9.]+%)(?:\s*[,\s/]+\s*([0-9.]+))?\s*\)$/i;

/**
 * Creates a Color instance from a CSS color value.
 *
 * @param {string} color The CSS color value in #rgb, #rgba, #rrggbb, #rrggbbaa, rgb(), rgba(), hsl(), or hsla() format.
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The color object, or undefined if the string was not a valid CSS color.
 *
 *
 * @example
 * const cesiumBlue = Cesium.Color.fromCssColorString('#67ADDF');
 * const green = Cesium.Color.fromCssColorString('green');
 *
 * @see {@link http://www.w3.org/TR/css3-color|CSS color values}
 */
Color.fromCssColorString = function (color, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.string("color", color);
  //>>includeEnd('debug');

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    result = new Color();
  }

  // Remove all surrounding whitespaces from the color string
  color = color.trim();

  const namedColor = Color[color.toUpperCase()];
  if ((0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(namedColor)) {
    Color.clone(namedColor, result);
    return result;
  }

  let matches = rgbaMatcher.exec(color);
  if (matches !== null) {
    result.red = parseInt(matches[1], 16) / 15;
    result.green = parseInt(matches[2], 16) / 15.0;
    result.blue = parseInt(matches[3], 16) / 15.0;
    result.alpha = parseInt((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(matches[4], "f"), 16) / 15.0;
    return result;
  }

  matches = rrggbbaaMatcher.exec(color);
  if (matches !== null) {
    result.red = parseInt(matches[1], 16) / 255.0;
    result.green = parseInt(matches[2], 16) / 255.0;
    result.blue = parseInt(matches[3], 16) / 255.0;
    result.alpha = parseInt((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(matches[4], "ff"), 16) / 255.0;
    return result;
  }

  matches = rgbParenthesesMatcher.exec(color);
  if (matches !== null) {
    result.red =
      parseFloat(matches[1]) / ("%" === matches[1].substr(-1) ? 100.0 : 255.0);
    result.green =
      parseFloat(matches[2]) / ("%" === matches[2].substr(-1) ? 100.0 : 255.0);
    result.blue =
      parseFloat(matches[3]) / ("%" === matches[3].substr(-1) ? 100.0 : 255.0);
    result.alpha = parseFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(matches[4], "1.0"));
    return result;
  }

  matches = hslParenthesesMatcher.exec(color);
  if (matches !== null) {
    return Color.fromHsl(
      parseFloat(matches[1]) / 360.0,
      parseFloat(matches[2]) / 100.0,
      parseFloat(matches[3]) / 100.0,
      parseFloat((0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(matches[4], "1.0")),
      result
    );
  }

  result = undefined;
  return result;
};

/**
 * The number of elements used to pack the object into an array.
 * @type {number}
 */
Color.packedLength = 4;

/**
 * Stores the provided instance into the provided array.
 *
 * @param {Color} value The value to pack.
 * @param {number[]} array The array to pack into.
 * @param {number} [startingIndex=0] The index into the array at which to start packing the elements.
 *
 * @returns {number[]} The array that was packed into
 */
Color.pack = function (value, array, startingIndex) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("value", value);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].defined("array", array);
  //>>includeEnd('debug');

  startingIndex = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(startingIndex, 0);
  array[startingIndex++] = value.red;
  array[startingIndex++] = value.green;
  array[startingIndex++] = value.blue;
  array[startingIndex] = value.alpha;

  return array;
};

/**
 * Retrieves an instance from a packed array.
 *
 * @param {number[]} array The packed array.
 * @param {number} [startingIndex=0] The starting index of the element to be unpacked.
 * @param {Color} [result] The object into which to store the result.
 * @returns {Color} The modified result parameter or a new Color instance if one was not provided.
 */
Color.unpack = function (array, startingIndex, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].defined("array", array);
  //>>includeEnd('debug');

  startingIndex = (0,_defaultValue_js__WEBPACK_IMPORTED_MODULE_0__["default"])(startingIndex, 0);
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    result = new Color();
  }
  result.red = array[startingIndex++];
  result.green = array[startingIndex++];
  result.blue = array[startingIndex++];
  result.alpha = array[startingIndex];
  return result;
};

/**
 * Converts a 'byte' color component in the range of 0 to 255 into
 * a 'float' color component in the range of 0 to 1.0.
 *
 * @param {number} number The number to be converted.
 * @returns {number} The converted number.
 */
Color.byteToFloat = function (number) {
  return number / 255.0;
};

/**
 * Converts a 'float' color component in the range of 0 to 1.0 into
 * a 'byte' color component in the range of 0 to 255.
 *
 * @param {number} number The number to be converted.
 * @returns {number} The converted number.
 */
Color.floatToByte = function (number) {
  return number === 1.0 ? 255.0 : (number * 256.0) | 0;
};

/**
 * Duplicates a Color.
 *
 * @param {Color} color The Color to duplicate.
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The modified result parameter or a new instance if result was undefined. (Returns undefined if color is undefined)
 */
Color.clone = function (color, result) {
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(color)) {
    return undefined;
  }
  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return new Color(color.red, color.green, color.blue, color.alpha);
  }
  result.red = color.red;
  result.green = color.green;
  result.blue = color.blue;
  result.alpha = color.alpha;
  return result;
};

/**
 * Returns true if the first Color equals the second color.
 *
 * @param {Color} left The first Color to compare for equality.
 * @param {Color} right The second Color to compare for equality.
 * @returns {boolean} <code>true</code> if the Colors are equal; otherwise, <code>false</code>.
 */
Color.equals = function (left, right) {
  return (
    left === right || //
    ((0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(left) && //
      (0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(right) && //
      left.red === right.red && //
      left.green === right.green && //
      left.blue === right.blue && //
      left.alpha === right.alpha)
  );
};

/**
 * @private
 */
Color.equalsArray = function (color, array, offset) {
  return (
    color.red === array[offset] &&
    color.green === array[offset + 1] &&
    color.blue === array[offset + 2] &&
    color.alpha === array[offset + 3]
  );
};

/**
 * Returns a duplicate of a Color instance.
 *
 * @param {Color} [result] The object to store the result in, if undefined a new instance will be created.
 * @returns {Color} The modified result parameter or a new instance if result was undefined.
 */
Color.prototype.clone = function (result) {
  return Color.clone(this, result);
};

/**
 * Returns true if this Color equals other.
 *
 * @param {Color} other The Color to compare for equality.
 * @returns {boolean} <code>true</code> if the Colors are equal; otherwise, <code>false</code>.
 */
Color.prototype.equals = function (other) {
  return Color.equals(this, other);
};

/**
 * Returns <code>true</code> if this Color equals other componentwise within the specified epsilon.
 *
 * @param {Color} other The Color to compare for equality.
 * @param {number} [epsilon=0.0] The epsilon to use for equality testing.
 * @returns {boolean} <code>true</code> if the Colors are equal within the specified epsilon; otherwise, <code>false</code>.
 */
Color.prototype.equalsEpsilon = function (other, epsilon) {
  return (
    this === other || //
    ((0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(other) && //
      Math.abs(this.red - other.red) <= epsilon && //
      Math.abs(this.green - other.green) <= epsilon && //
      Math.abs(this.blue - other.blue) <= epsilon && //
      Math.abs(this.alpha - other.alpha) <= epsilon)
  );
};

/**
 * Creates a string representing this Color in the format '(red, green, blue, alpha)'.
 *
 * @returns {string} A string representing this Color in the format '(red, green, blue, alpha)'.
 */
Color.prototype.toString = function () {
  return `(${this.red}, ${this.green}, ${this.blue}, ${this.alpha})`;
};

/**
 * Creates a string containing the CSS color value for this color.
 *
 * @returns {string} The CSS equivalent of this color.
 *
 * @see {@link http://www.w3.org/TR/css3-color/#rgba-color|CSS RGB or RGBA color values}
 */
Color.prototype.toCssColorString = function () {
  const red = Color.floatToByte(this.red);
  const green = Color.floatToByte(this.green);
  const blue = Color.floatToByte(this.blue);
  if (this.alpha === 1) {
    return `rgb(${red},${green},${blue})`;
  }
  return `rgba(${red},${green},${blue},${this.alpha})`;
};

/**
 * Creates a string containing CSS hex string color value for this color.
 *
 * @returns {string} The CSS hex string equivalent of this color.
 */
Color.prototype.toCssHexString = function () {
  let r = Color.floatToByte(this.red).toString(16);
  if (r.length < 2) {
    r = `0${r}`;
  }
  let g = Color.floatToByte(this.green).toString(16);
  if (g.length < 2) {
    g = `0${g}`;
  }
  let b = Color.floatToByte(this.blue).toString(16);
  if (b.length < 2) {
    b = `0${b}`;
  }
  if (this.alpha < 1) {
    let hexAlpha = Color.floatToByte(this.alpha).toString(16);
    if (hexAlpha.length < 2) {
      hexAlpha = `0${hexAlpha}`;
    }
    return `#${r}${g}${b}${hexAlpha}`;
  }
  return `#${r}${g}${b}`;
};

/**
 * Converts this color to an array of red, green, blue, and alpha values
 * that are in the range of 0 to 255.
 *
 * @param {number[]} [result] The array to store the result in, if undefined a new instance will be created.
 * @returns {number[]} The modified result parameter or a new instance if result was undefined.
 */
Color.prototype.toBytes = function (result) {
  const red = Color.floatToByte(this.red);
  const green = Color.floatToByte(this.green);
  const blue = Color.floatToByte(this.blue);
  const alpha = Color.floatToByte(this.alpha);

  if (!(0,_defined_js__WEBPACK_IMPORTED_MODULE_2__["default"])(result)) {
    return [red, green, blue, alpha];
  }
  result[0] = red;
  result[1] = green;
  result[2] = blue;
  result[3] = alpha;
  return result;
};

/**
 * Converts this color to a single numeric unsigned 32-bit RGBA value, using the endianness
 * of the system.
 *
 * @returns {number} A single numeric unsigned 32-bit RGBA value.
 *
 *
 * @example
 * const rgba = Cesium.Color.BLUE.toRgba();
 *
 * @see Color.fromRgba
 */
Color.prototype.toRgba = function () {
  // scratchUint32Array and scratchUint8Array share an underlying array buffer
  scratchUint8Array[0] = Color.floatToByte(this.red);
  scratchUint8Array[1] = Color.floatToByte(this.green);
  scratchUint8Array[2] = Color.floatToByte(this.blue);
  scratchUint8Array[3] = Color.floatToByte(this.alpha);
  return scratchUint32Array[0];
};

/**
 * Brightens this color by the provided magnitude.
 *
 * @param {number} magnitude A positive number indicating the amount to brighten.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 *
 * @example
 * const brightBlue = Cesium.Color.BLUE.brighten(0.5, new Cesium.Color());
 */
Color.prototype.brighten = function (magnitude, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("magnitude", magnitude);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.greaterThanOrEquals("magnitude", magnitude, 0.0);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  magnitude = 1.0 - magnitude;
  result.red = 1.0 - (1.0 - this.red) * magnitude;
  result.green = 1.0 - (1.0 - this.green) * magnitude;
  result.blue = 1.0 - (1.0 - this.blue) * magnitude;
  result.alpha = this.alpha;
  return result;
};

/**
 * Darkens this color by the provided magnitude.
 *
 * @param {number} magnitude A positive number indicating the amount to darken.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 *
 * @example
 * const darkBlue = Cesium.Color.BLUE.darken(0.5, new Cesium.Color());
 */
Color.prototype.darken = function (magnitude, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("magnitude", magnitude);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number.greaterThanOrEquals("magnitude", magnitude, 0.0);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  magnitude = 1.0 - magnitude;
  result.red = this.red * magnitude;
  result.green = this.green * magnitude;
  result.blue = this.blue * magnitude;
  result.alpha = this.alpha;
  return result;
};

/**
 * Creates a new Color that has the same red, green, and blue components
 * as this Color, but with the specified alpha value.
 *
 * @param {number} alpha The new alpha component.
 * @param {Color} [result] The object onto which to store the result.
 * @returns {Color} The modified result parameter or a new Color instance if one was not provided.
 *
 * @example const translucentRed = Cesium.Color.RED.withAlpha(0.9);
 */
Color.prototype.withAlpha = function (alpha, result) {
  return Color.fromAlpha(this, alpha, result);
};

/**
 * Computes the componentwise sum of two Colors.
 *
 * @param {Color} left The first Color.
 * @param {Color} right The second Color.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.add = function (left, right, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("left", left);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("right", right);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = left.red + right.red;
  result.green = left.green + right.green;
  result.blue = left.blue + right.blue;
  result.alpha = left.alpha + right.alpha;
  return result;
};

/**
 * Computes the componentwise difference of two Colors.
 *
 * @param {Color} left The first Color.
 * @param {Color} right The second Color.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.subtract = function (left, right, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("left", left);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("right", right);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = left.red - right.red;
  result.green = left.green - right.green;
  result.blue = left.blue - right.blue;
  result.alpha = left.alpha - right.alpha;
  return result;
};

/**
 * Computes the componentwise product of two Colors.
 *
 * @param {Color} left The first Color.
 * @param {Color} right The second Color.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.multiply = function (left, right, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("left", left);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("right", right);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = left.red * right.red;
  result.green = left.green * right.green;
  result.blue = left.blue * right.blue;
  result.alpha = left.alpha * right.alpha;
  return result;
};

/**
 * Computes the componentwise quotient of two Colors.
 *
 * @param {Color} left The first Color.
 * @param {Color} right The second Color.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.divide = function (left, right, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("left", left);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("right", right);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = left.red / right.red;
  result.green = left.green / right.green;
  result.blue = left.blue / right.blue;
  result.alpha = left.alpha / right.alpha;
  return result;
};

/**
 * Computes the componentwise modulus of two Colors.
 *
 * @param {Color} left The first Color.
 * @param {Color} right The second Color.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.mod = function (left, right, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("left", left);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("right", right);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = left.red % right.red;
  result.green = left.green % right.green;
  result.blue = left.blue % right.blue;
  result.alpha = left.alpha % right.alpha;
  return result;
};

/**
 * Computes the linear interpolation or extrapolation at t between the provided colors.
 *
 * @param {Color} start The color corresponding to t at 0.0.
 * @param {Color} end The color corresponding to t at 1.0.
 * @param {number} t The point along t at which to interpolate.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.lerp = function (start, end, t, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("start", start);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("end", end);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("t", t);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].lerp(start.red, end.red, t);
  result.green = _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].lerp(start.green, end.green, t);
  result.blue = _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].lerp(start.blue, end.blue, t);
  result.alpha = _Math_js__WEBPACK_IMPORTED_MODULE_4__["default"].lerp(start.alpha, end.alpha, t);
  return result;
};

/**
 * Multiplies the provided Color componentwise by the provided scalar.
 *
 * @param {Color} color The Color to be scaled.
 * @param {number} scalar The scalar to multiply with.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.multiplyByScalar = function (color, scalar, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("color", color);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("scalar", scalar);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = color.red * scalar;
  result.green = color.green * scalar;
  result.blue = color.blue * scalar;
  result.alpha = color.alpha * scalar;
  return result;
};

/**
 * Divides the provided Color componentwise by the provided scalar.
 *
 * @param {Color} color The Color to be divided.
 * @param {number} scalar The scalar to divide with.
 * @param {Color} result The object onto which to store the result.
 * @returns {Color} The modified result parameter.
 */
Color.divideByScalar = function (color, scalar, result) {
  //>>includeStart('debug', pragmas.debug);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("color", color);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.number("scalar", scalar);
  _Check_js__WEBPACK_IMPORTED_MODULE_1__["default"].typeOf.object("result", result);
  //>>includeEnd('debug');

  result.red = color.red / scalar;
  result.green = color.green / scalar;
  result.blue = color.blue / scalar;
  result.alpha = color.alpha / scalar;
  return result;
};

/**
 * An immutable Color instance initialized to CSS color #F0F8FF
 * <span class="colorSwath" style="background: #F0F8FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ALICEBLUE = Object.freeze(Color.fromCssColorString("#F0F8FF"));

/**
 * An immutable Color instance initialized to CSS color #FAEBD7
 * <span class="colorSwath" style="background: #FAEBD7;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ANTIQUEWHITE = Object.freeze(Color.fromCssColorString("#FAEBD7"));

/**
 * An immutable Color instance initialized to CSS color #00FFFF
 * <span class="colorSwath" style="background: #00FFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.AQUA = Object.freeze(Color.fromCssColorString("#00FFFF"));

/**
 * An immutable Color instance initialized to CSS color #7FFFD4
 * <span class="colorSwath" style="background: #7FFFD4;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.AQUAMARINE = Object.freeze(Color.fromCssColorString("#7FFFD4"));

/**
 * An immutable Color instance initialized to CSS color #F0FFFF
 * <span class="colorSwath" style="background: #F0FFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.AZURE = Object.freeze(Color.fromCssColorString("#F0FFFF"));

/**
 * An immutable Color instance initialized to CSS color #F5F5DC
 * <span class="colorSwath" style="background: #F5F5DC;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BEIGE = Object.freeze(Color.fromCssColorString("#F5F5DC"));

/**
 * An immutable Color instance initialized to CSS color #FFE4C4
 * <span class="colorSwath" style="background: #FFE4C4;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BISQUE = Object.freeze(Color.fromCssColorString("#FFE4C4"));

/**
 * An immutable Color instance initialized to CSS color #000000
 * <span class="colorSwath" style="background: #000000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BLACK = Object.freeze(Color.fromCssColorString("#000000"));

/**
 * An immutable Color instance initialized to CSS color #FFEBCD
 * <span class="colorSwath" style="background: #FFEBCD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BLANCHEDALMOND = Object.freeze(Color.fromCssColorString("#FFEBCD"));

/**
 * An immutable Color instance initialized to CSS color #0000FF
 * <span class="colorSwath" style="background: #0000FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BLUE = Object.freeze(Color.fromCssColorString("#0000FF"));

/**
 * An immutable Color instance initialized to CSS color #8A2BE2
 * <span class="colorSwath" style="background: #8A2BE2;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BLUEVIOLET = Object.freeze(Color.fromCssColorString("#8A2BE2"));

/**
 * An immutable Color instance initialized to CSS color #A52A2A
 * <span class="colorSwath" style="background: #A52A2A;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BROWN = Object.freeze(Color.fromCssColorString("#A52A2A"));

/**
 * An immutable Color instance initialized to CSS color #DEB887
 * <span class="colorSwath" style="background: #DEB887;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.BURLYWOOD = Object.freeze(Color.fromCssColorString("#DEB887"));

/**
 * An immutable Color instance initialized to CSS color #5F9EA0
 * <span class="colorSwath" style="background: #5F9EA0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CADETBLUE = Object.freeze(Color.fromCssColorString("#5F9EA0"));
/**
 * An immutable Color instance initialized to CSS color #7FFF00
 * <span class="colorSwath" style="background: #7FFF00;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CHARTREUSE = Object.freeze(Color.fromCssColorString("#7FFF00"));

/**
 * An immutable Color instance initialized to CSS color #D2691E
 * <span class="colorSwath" style="background: #D2691E;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CHOCOLATE = Object.freeze(Color.fromCssColorString("#D2691E"));

/**
 * An immutable Color instance initialized to CSS color #FF7F50
 * <span class="colorSwath" style="background: #FF7F50;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CORAL = Object.freeze(Color.fromCssColorString("#FF7F50"));

/**
 * An immutable Color instance initialized to CSS color #6495ED
 * <span class="colorSwath" style="background: #6495ED;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CORNFLOWERBLUE = Object.freeze(Color.fromCssColorString("#6495ED"));

/**
 * An immutable Color instance initialized to CSS color #FFF8DC
 * <span class="colorSwath" style="background: #FFF8DC;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CORNSILK = Object.freeze(Color.fromCssColorString("#FFF8DC"));

/**
 * An immutable Color instance initialized to CSS color #DC143C
 * <span class="colorSwath" style="background: #DC143C;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CRIMSON = Object.freeze(Color.fromCssColorString("#DC143C"));

/**
 * An immutable Color instance initialized to CSS color #00FFFF
 * <span class="colorSwath" style="background: #00FFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.CYAN = Object.freeze(Color.fromCssColorString("#00FFFF"));

/**
 * An immutable Color instance initialized to CSS color #00008B
 * <span class="colorSwath" style="background: #00008B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKBLUE = Object.freeze(Color.fromCssColorString("#00008B"));

/**
 * An immutable Color instance initialized to CSS color #008B8B
 * <span class="colorSwath" style="background: #008B8B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKCYAN = Object.freeze(Color.fromCssColorString("#008B8B"));

/**
 * An immutable Color instance initialized to CSS color #B8860B
 * <span class="colorSwath" style="background: #B8860B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKGOLDENROD = Object.freeze(Color.fromCssColorString("#B8860B"));

/**
 * An immutable Color instance initialized to CSS color #A9A9A9
 * <span class="colorSwath" style="background: #A9A9A9;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKGRAY = Object.freeze(Color.fromCssColorString("#A9A9A9"));

/**
 * An immutable Color instance initialized to CSS color #006400
 * <span class="colorSwath" style="background: #006400;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKGREEN = Object.freeze(Color.fromCssColorString("#006400"));

/**
 * An immutable Color instance initialized to CSS color #A9A9A9
 * <span class="colorSwath" style="background: #A9A9A9;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKGREY = Color.DARKGRAY;

/**
 * An immutable Color instance initialized to CSS color #BDB76B
 * <span class="colorSwath" style="background: #BDB76B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKKHAKI = Object.freeze(Color.fromCssColorString("#BDB76B"));

/**
 * An immutable Color instance initialized to CSS color #8B008B
 * <span class="colorSwath" style="background: #8B008B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKMAGENTA = Object.freeze(Color.fromCssColorString("#8B008B"));

/**
 * An immutable Color instance initialized to CSS color #556B2F
 * <span class="colorSwath" style="background: #556B2F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKOLIVEGREEN = Object.freeze(Color.fromCssColorString("#556B2F"));

/**
 * An immutable Color instance initialized to CSS color #FF8C00
 * <span class="colorSwath" style="background: #FF8C00;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKORANGE = Object.freeze(Color.fromCssColorString("#FF8C00"));

/**
 * An immutable Color instance initialized to CSS color #9932CC
 * <span class="colorSwath" style="background: #9932CC;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKORCHID = Object.freeze(Color.fromCssColorString("#9932CC"));

/**
 * An immutable Color instance initialized to CSS color #8B0000
 * <span class="colorSwath" style="background: #8B0000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKRED = Object.freeze(Color.fromCssColorString("#8B0000"));

/**
 * An immutable Color instance initialized to CSS color #E9967A
 * <span class="colorSwath" style="background: #E9967A;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKSALMON = Object.freeze(Color.fromCssColorString("#E9967A"));

/**
 * An immutable Color instance initialized to CSS color #8FBC8F
 * <span class="colorSwath" style="background: #8FBC8F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKSEAGREEN = Object.freeze(Color.fromCssColorString("#8FBC8F"));

/**
 * An immutable Color instance initialized to CSS color #483D8B
 * <span class="colorSwath" style="background: #483D8B;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKSLATEBLUE = Object.freeze(Color.fromCssColorString("#483D8B"));

/**
 * An immutable Color instance initialized to CSS color #2F4F4F
 * <span class="colorSwath" style="background: #2F4F4F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKSLATEGRAY = Object.freeze(Color.fromCssColorString("#2F4F4F"));

/**
 * An immutable Color instance initialized to CSS color #2F4F4F
 * <span class="colorSwath" style="background: #2F4F4F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKSLATEGREY = Color.DARKSLATEGRAY;

/**
 * An immutable Color instance initialized to CSS color #00CED1
 * <span class="colorSwath" style="background: #00CED1;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKTURQUOISE = Object.freeze(Color.fromCssColorString("#00CED1"));

/**
 * An immutable Color instance initialized to CSS color #9400D3
 * <span class="colorSwath" style="background: #9400D3;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DARKVIOLET = Object.freeze(Color.fromCssColorString("#9400D3"));

/**
 * An immutable Color instance initialized to CSS color #FF1493
 * <span class="colorSwath" style="background: #FF1493;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DEEPPINK = Object.freeze(Color.fromCssColorString("#FF1493"));

/**
 * An immutable Color instance initialized to CSS color #00BFFF
 * <span class="colorSwath" style="background: #00BFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DEEPSKYBLUE = Object.freeze(Color.fromCssColorString("#00BFFF"));

/**
 * An immutable Color instance initialized to CSS color #696969
 * <span class="colorSwath" style="background: #696969;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DIMGRAY = Object.freeze(Color.fromCssColorString("#696969"));

/**
 * An immutable Color instance initialized to CSS color #696969
 * <span class="colorSwath" style="background: #696969;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DIMGREY = Color.DIMGRAY;

/**
 * An immutable Color instance initialized to CSS color #1E90FF
 * <span class="colorSwath" style="background: #1E90FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.DODGERBLUE = Object.freeze(Color.fromCssColorString("#1E90FF"));

/**
 * An immutable Color instance initialized to CSS color #B22222
 * <span class="colorSwath" style="background: #B22222;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.FIREBRICK = Object.freeze(Color.fromCssColorString("#B22222"));

/**
 * An immutable Color instance initialized to CSS color #FFFAF0
 * <span class="colorSwath" style="background: #FFFAF0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.FLORALWHITE = Object.freeze(Color.fromCssColorString("#FFFAF0"));

/**
 * An immutable Color instance initialized to CSS color #228B22
 * <span class="colorSwath" style="background: #228B22;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.FORESTGREEN = Object.freeze(Color.fromCssColorString("#228B22"));

/**
 * An immutable Color instance initialized to CSS color #FF00FF
 * <span class="colorSwath" style="background: #FF00FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.FUCHSIA = Object.freeze(Color.fromCssColorString("#FF00FF"));

/**
 * An immutable Color instance initialized to CSS color #DCDCDC
 * <span class="colorSwath" style="background: #DCDCDC;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GAINSBORO = Object.freeze(Color.fromCssColorString("#DCDCDC"));

/**
 * An immutable Color instance initialized to CSS color #F8F8FF
 * <span class="colorSwath" style="background: #F8F8FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GHOSTWHITE = Object.freeze(Color.fromCssColorString("#F8F8FF"));

/**
 * An immutable Color instance initialized to CSS color #FFD700
 * <span class="colorSwath" style="background: #FFD700;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GOLD = Object.freeze(Color.fromCssColorString("#FFD700"));

/**
 * An immutable Color instance initialized to CSS color #DAA520
 * <span class="colorSwath" style="background: #DAA520;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GOLDENROD = Object.freeze(Color.fromCssColorString("#DAA520"));

/**
 * An immutable Color instance initialized to CSS color #808080
 * <span class="colorSwath" style="background: #808080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GRAY = Object.freeze(Color.fromCssColorString("#808080"));

/**
 * An immutable Color instance initialized to CSS color #008000
 * <span class="colorSwath" style="background: #008000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GREEN = Object.freeze(Color.fromCssColorString("#008000"));

/**
 * An immutable Color instance initialized to CSS color #ADFF2F
 * <span class="colorSwath" style="background: #ADFF2F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GREENYELLOW = Object.freeze(Color.fromCssColorString("#ADFF2F"));

/**
 * An immutable Color instance initialized to CSS color #808080
 * <span class="colorSwath" style="background: #808080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.GREY = Color.GRAY;

/**
 * An immutable Color instance initialized to CSS color #F0FFF0
 * <span class="colorSwath" style="background: #F0FFF0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.HONEYDEW = Object.freeze(Color.fromCssColorString("#F0FFF0"));

/**
 * An immutable Color instance initialized to CSS color #FF69B4
 * <span class="colorSwath" style="background: #FF69B4;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.HOTPINK = Object.freeze(Color.fromCssColorString("#FF69B4"));

/**
 * An immutable Color instance initialized to CSS color #CD5C5C
 * <span class="colorSwath" style="background: #CD5C5C;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.INDIANRED = Object.freeze(Color.fromCssColorString("#CD5C5C"));

/**
 * An immutable Color instance initialized to CSS color #4B0082
 * <span class="colorSwath" style="background: #4B0082;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.INDIGO = Object.freeze(Color.fromCssColorString("#4B0082"));

/**
 * An immutable Color instance initialized to CSS color #FFFFF0
 * <span class="colorSwath" style="background: #FFFFF0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.IVORY = Object.freeze(Color.fromCssColorString("#FFFFF0"));

/**
 * An immutable Color instance initialized to CSS color #F0E68C
 * <span class="colorSwath" style="background: #F0E68C;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.KHAKI = Object.freeze(Color.fromCssColorString("#F0E68C"));

/**
 * An immutable Color instance initialized to CSS color #E6E6FA
 * <span class="colorSwath" style="background: #E6E6FA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LAVENDER = Object.freeze(Color.fromCssColorString("#E6E6FA"));

/**
 * An immutable Color instance initialized to CSS color #FFF0F5
 * <span class="colorSwath" style="background: #FFF0F5;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LAVENDAR_BLUSH = Object.freeze(Color.fromCssColorString("#FFF0F5"));

/**
 * An immutable Color instance initialized to CSS color #7CFC00
 * <span class="colorSwath" style="background: #7CFC00;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LAWNGREEN = Object.freeze(Color.fromCssColorString("#7CFC00"));

/**
 * An immutable Color instance initialized to CSS color #FFFACD
 * <span class="colorSwath" style="background: #FFFACD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LEMONCHIFFON = Object.freeze(Color.fromCssColorString("#FFFACD"));

/**
 * An immutable Color instance initialized to CSS color #ADD8E6
 * <span class="colorSwath" style="background: #ADD8E6;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTBLUE = Object.freeze(Color.fromCssColorString("#ADD8E6"));

/**
 * An immutable Color instance initialized to CSS color #F08080
 * <span class="colorSwath" style="background: #F08080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTCORAL = Object.freeze(Color.fromCssColorString("#F08080"));

/**
 * An immutable Color instance initialized to CSS color #E0FFFF
 * <span class="colorSwath" style="background: #E0FFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTCYAN = Object.freeze(Color.fromCssColorString("#E0FFFF"));

/**
 * An immutable Color instance initialized to CSS color #FAFAD2
 * <span class="colorSwath" style="background: #FAFAD2;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTGOLDENRODYELLOW = Object.freeze(Color.fromCssColorString("#FAFAD2"));

/**
 * An immutable Color instance initialized to CSS color #D3D3D3
 * <span class="colorSwath" style="background: #D3D3D3;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTGRAY = Object.freeze(Color.fromCssColorString("#D3D3D3"));

/**
 * An immutable Color instance initialized to CSS color #90EE90
 * <span class="colorSwath" style="background: #90EE90;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTGREEN = Object.freeze(Color.fromCssColorString("#90EE90"));

/**
 * An immutable Color instance initialized to CSS color #D3D3D3
 * <span class="colorSwath" style="background: #D3D3D3;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTGREY = Color.LIGHTGRAY;

/**
 * An immutable Color instance initialized to CSS color #FFB6C1
 * <span class="colorSwath" style="background: #FFB6C1;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTPINK = Object.freeze(Color.fromCssColorString("#FFB6C1"));

/**
 * An immutable Color instance initialized to CSS color #20B2AA
 * <span class="colorSwath" style="background: #20B2AA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTSEAGREEN = Object.freeze(Color.fromCssColorString("#20B2AA"));

/**
 * An immutable Color instance initialized to CSS color #87CEFA
 * <span class="colorSwath" style="background: #87CEFA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTSKYBLUE = Object.freeze(Color.fromCssColorString("#87CEFA"));

/**
 * An immutable Color instance initialized to CSS color #778899
 * <span class="colorSwath" style="background: #778899;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTSLATEGRAY = Object.freeze(Color.fromCssColorString("#778899"));

/**
 * An immutable Color instance initialized to CSS color #778899
 * <span class="colorSwath" style="background: #778899;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTSLATEGREY = Color.LIGHTSLATEGRAY;

/**
 * An immutable Color instance initialized to CSS color #B0C4DE
 * <span class="colorSwath" style="background: #B0C4DE;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTSTEELBLUE = Object.freeze(Color.fromCssColorString("#B0C4DE"));

/**
 * An immutable Color instance initialized to CSS color #FFFFE0
 * <span class="colorSwath" style="background: #FFFFE0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIGHTYELLOW = Object.freeze(Color.fromCssColorString("#FFFFE0"));

/**
 * An immutable Color instance initialized to CSS color #00FF00
 * <span class="colorSwath" style="background: #00FF00;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIME = Object.freeze(Color.fromCssColorString("#00FF00"));

/**
 * An immutable Color instance initialized to CSS color #32CD32
 * <span class="colorSwath" style="background: #32CD32;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LIMEGREEN = Object.freeze(Color.fromCssColorString("#32CD32"));

/**
 * An immutable Color instance initialized to CSS color #FAF0E6
 * <span class="colorSwath" style="background: #FAF0E6;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.LINEN = Object.freeze(Color.fromCssColorString("#FAF0E6"));

/**
 * An immutable Color instance initialized to CSS color #FF00FF
 * <span class="colorSwath" style="background: #FF00FF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MAGENTA = Object.freeze(Color.fromCssColorString("#FF00FF"));

/**
 * An immutable Color instance initialized to CSS color #800000
 * <span class="colorSwath" style="background: #800000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MAROON = Object.freeze(Color.fromCssColorString("#800000"));

/**
 * An immutable Color instance initialized to CSS color #66CDAA
 * <span class="colorSwath" style="background: #66CDAA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMAQUAMARINE = Object.freeze(Color.fromCssColorString("#66CDAA"));

/**
 * An immutable Color instance initialized to CSS color #0000CD
 * <span class="colorSwath" style="background: #0000CD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMBLUE = Object.freeze(Color.fromCssColorString("#0000CD"));

/**
 * An immutable Color instance initialized to CSS color #BA55D3
 * <span class="colorSwath" style="background: #BA55D3;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMORCHID = Object.freeze(Color.fromCssColorString("#BA55D3"));

/**
 * An immutable Color instance initialized to CSS color #9370DB
 * <span class="colorSwath" style="background: #9370DB;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMPURPLE = Object.freeze(Color.fromCssColorString("#9370DB"));

/**
 * An immutable Color instance initialized to CSS color #3CB371
 * <span class="colorSwath" style="background: #3CB371;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMSEAGREEN = Object.freeze(Color.fromCssColorString("#3CB371"));

/**
 * An immutable Color instance initialized to CSS color #7B68EE
 * <span class="colorSwath" style="background: #7B68EE;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMSLATEBLUE = Object.freeze(Color.fromCssColorString("#7B68EE"));

/**
 * An immutable Color instance initialized to CSS color #00FA9A
 * <span class="colorSwath" style="background: #00FA9A;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMSPRINGGREEN = Object.freeze(Color.fromCssColorString("#00FA9A"));

/**
 * An immutable Color instance initialized to CSS color #48D1CC
 * <span class="colorSwath" style="background: #48D1CC;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMTURQUOISE = Object.freeze(Color.fromCssColorString("#48D1CC"));

/**
 * An immutable Color instance initialized to CSS color #C71585
 * <span class="colorSwath" style="background: #C71585;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MEDIUMVIOLETRED = Object.freeze(Color.fromCssColorString("#C71585"));

/**
 * An immutable Color instance initialized to CSS color #191970
 * <span class="colorSwath" style="background: #191970;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MIDNIGHTBLUE = Object.freeze(Color.fromCssColorString("#191970"));

/**
 * An immutable Color instance initialized to CSS color #F5FFFA
 * <span class="colorSwath" style="background: #F5FFFA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MINTCREAM = Object.freeze(Color.fromCssColorString("#F5FFFA"));

/**
 * An immutable Color instance initialized to CSS color #FFE4E1
 * <span class="colorSwath" style="background: #FFE4E1;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MISTYROSE = Object.freeze(Color.fromCssColorString("#FFE4E1"));

/**
 * An immutable Color instance initialized to CSS color #FFE4B5
 * <span class="colorSwath" style="background: #FFE4B5;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.MOCCASIN = Object.freeze(Color.fromCssColorString("#FFE4B5"));

/**
 * An immutable Color instance initialized to CSS color #FFDEAD
 * <span class="colorSwath" style="background: #FFDEAD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.NAVAJOWHITE = Object.freeze(Color.fromCssColorString("#FFDEAD"));

/**
 * An immutable Color instance initialized to CSS color #000080
 * <span class="colorSwath" style="background: #000080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.NAVY = Object.freeze(Color.fromCssColorString("#000080"));

/**
 * An immutable Color instance initialized to CSS color #FDF5E6
 * <span class="colorSwath" style="background: #FDF5E6;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.OLDLACE = Object.freeze(Color.fromCssColorString("#FDF5E6"));

/**
 * An immutable Color instance initialized to CSS color #808000
 * <span class="colorSwath" style="background: #808000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.OLIVE = Object.freeze(Color.fromCssColorString("#808000"));

/**
 * An immutable Color instance initialized to CSS color #6B8E23
 * <span class="colorSwath" style="background: #6B8E23;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.OLIVEDRAB = Object.freeze(Color.fromCssColorString("#6B8E23"));

/**
 * An immutable Color instance initialized to CSS color #FFA500
 * <span class="colorSwath" style="background: #FFA500;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ORANGE = Object.freeze(Color.fromCssColorString("#FFA500"));

/**
 * An immutable Color instance initialized to CSS color #FF4500
 * <span class="colorSwath" style="background: #FF4500;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ORANGERED = Object.freeze(Color.fromCssColorString("#FF4500"));

/**
 * An immutable Color instance initialized to CSS color #DA70D6
 * <span class="colorSwath" style="background: #DA70D6;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ORCHID = Object.freeze(Color.fromCssColorString("#DA70D6"));

/**
 * An immutable Color instance initialized to CSS color #EEE8AA
 * <span class="colorSwath" style="background: #EEE8AA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PALEGOLDENROD = Object.freeze(Color.fromCssColorString("#EEE8AA"));

/**
 * An immutable Color instance initialized to CSS color #98FB98
 * <span class="colorSwath" style="background: #98FB98;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PALEGREEN = Object.freeze(Color.fromCssColorString("#98FB98"));

/**
 * An immutable Color instance initialized to CSS color #AFEEEE
 * <span class="colorSwath" style="background: #AFEEEE;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PALETURQUOISE = Object.freeze(Color.fromCssColorString("#AFEEEE"));

/**
 * An immutable Color instance initialized to CSS color #DB7093
 * <span class="colorSwath" style="background: #DB7093;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PALEVIOLETRED = Object.freeze(Color.fromCssColorString("#DB7093"));

/**
 * An immutable Color instance initialized to CSS color #FFEFD5
 * <span class="colorSwath" style="background: #FFEFD5;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PAPAYAWHIP = Object.freeze(Color.fromCssColorString("#FFEFD5"));

/**
 * An immutable Color instance initialized to CSS color #FFDAB9
 * <span class="colorSwath" style="background: #FFDAB9;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PEACHPUFF = Object.freeze(Color.fromCssColorString("#FFDAB9"));

/**
 * An immutable Color instance initialized to CSS color #CD853F
 * <span class="colorSwath" style="background: #CD853F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PERU = Object.freeze(Color.fromCssColorString("#CD853F"));

/**
 * An immutable Color instance initialized to CSS color #FFC0CB
 * <span class="colorSwath" style="background: #FFC0CB;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PINK = Object.freeze(Color.fromCssColorString("#FFC0CB"));

/**
 * An immutable Color instance initialized to CSS color #DDA0DD
 * <span class="colorSwath" style="background: #DDA0DD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PLUM = Object.freeze(Color.fromCssColorString("#DDA0DD"));

/**
 * An immutable Color instance initialized to CSS color #B0E0E6
 * <span class="colorSwath" style="background: #B0E0E6;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.POWDERBLUE = Object.freeze(Color.fromCssColorString("#B0E0E6"));

/**
 * An immutable Color instance initialized to CSS color #800080
 * <span class="colorSwath" style="background: #800080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.PURPLE = Object.freeze(Color.fromCssColorString("#800080"));

/**
 * An immutable Color instance initialized to CSS color #FF0000
 * <span class="colorSwath" style="background: #FF0000;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.RED = Object.freeze(Color.fromCssColorString("#FF0000"));

/**
 * An immutable Color instance initialized to CSS color #BC8F8F
 * <span class="colorSwath" style="background: #BC8F8F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ROSYBROWN = Object.freeze(Color.fromCssColorString("#BC8F8F"));

/**
 * An immutable Color instance initialized to CSS color #4169E1
 * <span class="colorSwath" style="background: #4169E1;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.ROYALBLUE = Object.freeze(Color.fromCssColorString("#4169E1"));

/**
 * An immutable Color instance initialized to CSS color #8B4513
 * <span class="colorSwath" style="background: #8B4513;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SADDLEBROWN = Object.freeze(Color.fromCssColorString("#8B4513"));

/**
 * An immutable Color instance initialized to CSS color #FA8072
 * <span class="colorSwath" style="background: #FA8072;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SALMON = Object.freeze(Color.fromCssColorString("#FA8072"));

/**
 * An immutable Color instance initialized to CSS color #F4A460
 * <span class="colorSwath" style="background: #F4A460;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SANDYBROWN = Object.freeze(Color.fromCssColorString("#F4A460"));

/**
 * An immutable Color instance initialized to CSS color #2E8B57
 * <span class="colorSwath" style="background: #2E8B57;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SEAGREEN = Object.freeze(Color.fromCssColorString("#2E8B57"));

/**
 * An immutable Color instance initialized to CSS color #FFF5EE
 * <span class="colorSwath" style="background: #FFF5EE;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SEASHELL = Object.freeze(Color.fromCssColorString("#FFF5EE"));

/**
 * An immutable Color instance initialized to CSS color #A0522D
 * <span class="colorSwath" style="background: #A0522D;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SIENNA = Object.freeze(Color.fromCssColorString("#A0522D"));

/**
 * An immutable Color instance initialized to CSS color #C0C0C0
 * <span class="colorSwath" style="background: #C0C0C0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SILVER = Object.freeze(Color.fromCssColorString("#C0C0C0"));

/**
 * An immutable Color instance initialized to CSS color #87CEEB
 * <span class="colorSwath" style="background: #87CEEB;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SKYBLUE = Object.freeze(Color.fromCssColorString("#87CEEB"));

/**
 * An immutable Color instance initialized to CSS color #6A5ACD
 * <span class="colorSwath" style="background: #6A5ACD;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SLATEBLUE = Object.freeze(Color.fromCssColorString("#6A5ACD"));

/**
 * An immutable Color instance initialized to CSS color #708090
 * <span class="colorSwath" style="background: #708090;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SLATEGRAY = Object.freeze(Color.fromCssColorString("#708090"));

/**
 * An immutable Color instance initialized to CSS color #708090
 * <span class="colorSwath" style="background: #708090;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SLATEGREY = Color.SLATEGRAY;

/**
 * An immutable Color instance initialized to CSS color #FFFAFA
 * <span class="colorSwath" style="background: #FFFAFA;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SNOW = Object.freeze(Color.fromCssColorString("#FFFAFA"));

/**
 * An immutable Color instance initialized to CSS color #00FF7F
 * <span class="colorSwath" style="background: #00FF7F;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.SPRINGGREEN = Object.freeze(Color.fromCssColorString("#00FF7F"));

/**
 * An immutable Color instance initialized to CSS color #4682B4
 * <span class="colorSwath" style="background: #4682B4;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.STEELBLUE = Object.freeze(Color.fromCssColorString("#4682B4"));

/**
 * An immutable Color instance initialized to CSS color #D2B48C
 * <span class="colorSwath" style="background: #D2B48C;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.TAN = Object.freeze(Color.fromCssColorString("#D2B48C"));

/**
 * An immutable Color instance initialized to CSS color #008080
 * <span class="colorSwath" style="background: #008080;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.TEAL = Object.freeze(Color.fromCssColorString("#008080"));

/**
 * An immutable Color instance initialized to CSS color #D8BFD8
 * <span class="colorSwath" style="background: #D8BFD8;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.THISTLE = Object.freeze(Color.fromCssColorString("#D8BFD8"));

/**
 * An immutable Color instance initialized to CSS color #FF6347
 * <span class="colorSwath" style="background: #FF6347;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.TOMATO = Object.freeze(Color.fromCssColorString("#FF6347"));

/**
 * An immutable Color instance initialized to CSS color #40E0D0
 * <span class="colorSwath" style="background: #40E0D0;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.TURQUOISE = Object.freeze(Color.fromCssColorString("#40E0D0"));

/**
 * An immutable Color instance initialized to CSS color #EE82EE
 * <span class="colorSwath" style="background: #EE82EE;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.VIOLET = Object.freeze(Color.fromCssColorString("#EE82EE"));

/**
 * An immutable Color instance initialized to CSS color #F5DEB3
 * <span class="colorSwath" style="background: #F5DEB3;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.WHEAT = Object.freeze(Color.fromCssColorString("#F5DEB3"));

/**
 * An immutable Color instance initialized to CSS color #FFFFFF
 * <span class="colorSwath" style="background: #FFFFFF;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.WHITE = Object.freeze(Color.fromCssColorString("#FFFFFF"));

/**
 * An immutable Color instance initialized to CSS color #F5F5F5
 * <span class="colorSwath" style="background: #F5F5F5;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.WHITESMOKE = Object.freeze(Color.fromCssColorString("#F5F5F5"));

/**
 * An immutable Color instance initialized to CSS color #FFFF00
 * <span class="colorSwath" style="background: #FFFF00;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.YELLOW = Object.freeze(Color.fromCssColorString("#FFFF00"));

/**
 * An immutable Color instance initialized to CSS color #9ACD32
 * <span class="colorSwath" style="background: #9ACD32;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.YELLOWGREEN = Object.freeze(Color.fromCssColorString("#9ACD32"));

/**
 * An immutable Color instance initialized to CSS transparent.
 * <span class="colorSwath" style="background: transparent;"></span>
 *
 * @constant
 * @type {Color}
 */
Color.TRANSPARENT = Object.freeze(new Color(0, 0, 0, 0));
/* harmony default export */ __webpack_exports__["default"] = (Color);

}();
Color = __webpack_exports__["default"];
/******/ })()
;
