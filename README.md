Latch		{#mainpage}
=====

A Simple Regulator	{#regulator}
------------------
This is a simple mechanism to limit spammy operations where a single execution
will suffice.

Logging messages in a loop is a good application for this,
especially if that log is being written to a file. Instead, you have one line
from the first iteration, where the latch is set. No additional lines will be
written, until a condition is met that unsets the latch.

