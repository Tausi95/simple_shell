#include "shell.h"

/**
 * _myexit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			info->err_num = exit_status;
			return (1);
		}
		info->err_num = exit_status;
	}

	return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *dir;
	char buffer[1024];

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(getcwd(buffer, 1024));
			_putchar('\n');
			return (1);
		}
		_puts(dir);
		_putchar('\n');
	}
	else
	{
		dir = info->argv[1];
	}

	if (chdir(dir) == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * _myhelp - Prints help message. Function not yet implemented.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	_puts("help call works. Function not yet implemented\n");
	return (0);
}
