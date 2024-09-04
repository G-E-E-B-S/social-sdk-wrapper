'use strict';
const path = require('path');

// Developer's custom module configuration
// configList is required
const configList = [
  [ 'social.i', 'jsb_social_auto.cpp' ]
];

const projectRoot = path.resolve(path.join(__dirname));
// bindingsOutDir is optional
const bindingsOutDir = path.join(projectRoot, 'bindings', 'auto', '3.7.x');

module.exports = {
  bindingsOutDir, // optional, if it isn't exported, the items in configList should be absolute or relative to current directory of swig-config.js
  configList // required
};
