#pragma once

class Tester
{
public:
	/// <summary>
	/// ruleaza toate testele
	/// </summary>
	void runAll() const noexcept;
private:
	/// <summary>
	/// ruleaza teste Melodie
	/// </summary>
	void runDomainTests() const noexcept;

	/// <summary>
	/// ruleaza teste Repo
	/// </summary>
	void runRepoTests() const noexcept;

	/// <summary>
	/// ruleaza teste Service
	/// </summary>
	void runServiceTests() const noexcept;
};

