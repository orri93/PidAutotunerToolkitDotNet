function log(message) {
  console.log(message);
}
function log(file, message) {
  console.log(file + " - " + message);
}

function PathValidatorType(type) {
  switch (type) {
    case "Any":
    case "any":
      return 0;
    case "Directory":
    case "directory":
      return 1;
    case "File":
    case "file":
      return 2;
    default:
      return 0;
  }
}

function PathValidatorRestriction(restriction) {
  switch (restriction) {
    case "None":
    case "none":
      return 0;
    case "Exists":
    case "exists":
      return 1;
    case "NotExists":
    case "notExists":
    case "notexists":
    case "not_exists":
      return 2;
    case "Absolute":
    case "absolute":
      return 4;
    case "ExistsAbsolute":
    case "existsAbsolute":
    case "existsabsolute":
    case "exists_absolute":
      return 5;
    case "NotExistsAbsolute":
    case "notExistsAbsolute":
    case "notexistsabsolute":
    case "not_exists_absolute":
      return 6;
    default:
      return 0;
  }
}
