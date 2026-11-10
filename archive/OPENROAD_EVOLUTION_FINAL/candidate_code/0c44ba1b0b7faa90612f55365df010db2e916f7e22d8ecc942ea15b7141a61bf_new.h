// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55112339;
  double density_weight = 0.24933553;
  double prefix_weight = 0.16805748;
  double neighborhood_weight = 0.31601783;
  double late_weight = 0.18590904;
  double critical_weight = 0.35673936;
  unsigned budget = 29;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
