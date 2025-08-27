import tokenize
import io
import textdistance
from io import StringIO


def remove_comments_and_docstrings(source):
    """
    Returns 'source' minus comments and docstrings.
    """
    io_obj = StringIO(source)
    out = ""
    prev_toktype = tokenize.INDENT
    last_lineno = -1
    last_col = 0
    for tok in tokenize.generate_tokens(io_obj.readline):
        token_type = tok[0]
        token_string = tok[1]
        start_line, start_col = tok[2]
        end_line, end_col = tok[3]
        ltext = tok[4]
        # The following two conditionals preserve indentation.
        # This is necessary because we're not using tokenize.untokenize()
        # (because it spits out code with copious amounts of oddly-placed
        # whitespace).
        if start_line > last_lineno:
            last_col = 0
        if start_col > last_col:
            out += (" " * (start_col - last_col))
        # Remove comments:
        if token_type == tokenize.COMMENT:
            pass
        # This series of conditionals removes docstrings:
        elif token_type == tokenize.STRING:
            if prev_toktype != tokenize.INDENT:
                # This is likely a docstring; double-check we're not inside an operator:
                if prev_toktype != tokenize.NEWLINE:
                    # Note regarding NEWLINE vs NL: The tokenize module
                    # differentiates between newlines that start a new statement
                    # and newlines inside of operators such as parens, brackes,
                    # and curly braces.  Newlines inside of operators are
                    # NEWLINE and newlines that start new code are NL.
                    # Catch whole-module docstrings:
                    if start_col > 0:
                        # Unlabelled indentation means we're inside an operator
                        out += token_string
                    # Note regarding the INDENT token: The tokenize module does
                    # not label indentation inside of an operator (parens,
                    # brackets, and curly braces) as actual indentation.
                    # For example:
                    # def foo():
                    #     "The spaces before this docstring are tokenize.INDENT"
                    #     test = [
                    #         "The spaces before this string do not get a token"
                    #     ]
        else:
            out += token_string
        prev_toktype = token_type
        last_col = end_col
        last_lineno = end_line
    return out


def tokening(code):
    input_encoding = io.BytesIO(code.encode("utf-8")).readline
    toks = list(tokenize.tokenize(input_encoding))[1:-1]
    llmtle_toks = [(tokenize.tok_name[t.type], t.string) for t in toks]
    if len(code) > 0 and llmtle_toks[-1][0] == "NEWLINE":  # treat NEWLINE
        llmtle_toks = llmtle_toks[:-1]

    ours_processed = []
    for tok in llmtle_toks:
        ours_processed.append(tok)
    return ours_processed


def token_edit_distance(code1, code2):
    try:
        processed_tokens1 = tokening(remove_comments_and_docstrings(code1))
    except:
        return -2
    try:
        processed_tokens2 = tokening(remove_comments_and_docstrings(code2))
    except:
        return -3

    tokens1_levenshtein = [t[-1] for t in processed_tokens1]
    tokens2_levenshtein = [t[-1] for t in processed_tokens2]

    return textdistance.levenshtein(tokens1_levenshtein, tokens2_levenshtein)

# def main():
