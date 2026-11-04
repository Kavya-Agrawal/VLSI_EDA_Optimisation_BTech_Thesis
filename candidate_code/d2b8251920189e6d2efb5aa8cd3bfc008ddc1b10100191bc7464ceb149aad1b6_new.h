// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80742444;
  double density_weight = 0.16045007;
  double prefix_weight = 0.39101921;
  double neighborhood_weight = 0.38359841;
  double late_weight = 0.16940103;
  double critical_weight = 0.23658382;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
