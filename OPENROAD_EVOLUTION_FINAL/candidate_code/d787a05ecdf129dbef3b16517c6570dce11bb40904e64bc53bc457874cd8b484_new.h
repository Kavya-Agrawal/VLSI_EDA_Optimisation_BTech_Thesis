// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88778689;
  double density_weight = 0.04983361;
  double prefix_weight = 0.23411407;
  double neighborhood_weight = 0.38437467;
  double late_weight = 0.09266587;
  double critical_weight = 0.45695106;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
